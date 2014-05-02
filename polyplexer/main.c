

/******************************************************************
 *
 * @author: Skapin <skapinthefourb@gmail.com> &&  kéké <3
 * @since: Oct. 2013
 * 
 * Multiplexer for virtual serial device. Handle input and dipstach to the corretc device.
 * Virtual device name shoudl be created with another software. 
 * Look virtu-serial for futher information about this
 *
 ******************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <poll.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "Color.h"

#define FD_NUMBER 3
#define ARG_SIZE 1024
#define BUFFER_SIZE 1024*4
#define DATA_READY 0
#define DATA_CLEARED_OVERFLOW 42
#define DATA_WAITING_MORE 1
#define DATA_NOTHING_NEW 2
#define DATA_CLOSED 3
#define DATA_ERROR 3

#ifndef VERBOSE 
 #define VERBOSE 0
#else
 #define VERBOSE 1
#endif

/*  Debug printf to stderr.   */
#define eprintf(fmt, ...) \
            do { if (VERBOSE) fprintf (stdout, fmt, ##__VA_ARGS__) ; } while (0)

/*  Globals Vars. */
struct pollfd fds[FD_NUMBER];
char input_buffer[FD_NUMBER][BUFFER_SIZE];
char tmp_buffer[BUFFER_SIZE];
int current_size[FD_NUMBER]={0,0,0};
int baudrate = 115200;
//int baudrate = 9600;
int printer=2, poly=1, serial=0;
int i;

void abandon_c(char r[], int code)
{
  perror(r);
  exit(code);
}
void abandon(char r[])
{
  abandon_c(r, EXIT_FAILURE);
}


void clear_stream(int fd_id)
{
  memset(input_buffer[fd_id], 0, sizeof(input_buffer[fd_id]));
  current_size[fd_id] = 0;
}

/*  Define a fd as a pty/serial file with a given baudrate.  */
int set_as_pty(int fd, int baudrate)
{
  /* serial port parameters */
    struct termios toptions;
    /* memset(&newtio, 0, sizeof(newtio));
       struct termios oldtio;*/
    if (tcgetattr(fd, &toptions) < 0) {
      perror("Open Port PTYt: Couldn't get term attributes");
      return -1;
    }
    //    tcgetattr(fd, &toptions);

    speed_t brate = baudrate; // let you override switch below if needed
    switch(baudrate) {
    case 4800: brate=B4800; break;
    case 9600: brate=B9600; break;
#ifdef B14400
    case 14400: brate=B14400; break;
#endif
    case 19200: brate=B19200; break;
#ifdef B28800
    case 28800: brate=B28800; break;
#endif
    case 38400: brate=B38400; break;
    case 57600: brate=B57600; break;
    case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);

    /*    cfsetispeed(&toptions, baudrate);
    cfsetospeed(&toptions, baudrate);
    */
    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;

    //toptions.c_cflag &= ~HUPCL; // disable hang-up-on-close to avoid reset

    toptions.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw

    toptions.c_cc[VMIN] = 0;
    toptions.c_cc[VTIME] = 0;
    
    tcsetattr(fd, TCSANOW, &toptions);
    if( tcsetattr(fd, TCSAFLUSH, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return 4;
    }
    return 0;
}

int read_stream(int fd_id)
{
  int nbr_read=0;
  memset( tmp_buffer, 0, sizeof(tmp_buffer) );
  nbr_read = read( fds[fd_id].fd, tmp_buffer, BUFFER_SIZE);
  if ( nbr_read > 0 ) /*  some datat to read */
    {
      current_size[fd_id] += nbr_read; /* We move the string tail mem. */
      if ( current_size[fd_id] > BUFFER_SIZE ) /*  Is too much data ? */
	{
	  color_text(RED);
	  eprintf("===[ERROR]  Way too much data... I can't handle it. Deleting the buffer for: %d\n", fd_id );
	  color_reset();

	  clear_stream( fd_id );
	  return DATA_CLEARED_OVERFLOW;
	}
      else
	{
	  strcat( input_buffer[fd_id], tmp_buffer ); /*  We copy the tmp string inside the correct buffer */
	  if ( input_buffer[fd_id][current_size[fd_id]-1] == '\n' || input_buffer[fd_id][current_size[fd_id]-1] == '\r' /*pos != NULL*/  /*|| pos2 != NULL*/ ) /* end found  */
	    {
	      return DATA_READY;
	    }
	  else
	    {
	      return DATA_WAITING_MORE;
	    }
	}
      //	  eprintf("===> %s\n",input_buffer[fd_id]);
      //	  write( fds[rial].fd, input_buffer[printer], nbr_read);
    }
  else if ( nbr_read == 0 ) // file/socket closed. (EOF) 
    {
      return DATA_CLOSED;
    }
  else
    {
      return DATA_ERROR;
    }
}

/*  open a given device and store it inside fds struct */
int init_stream(char* devicename, int device_id)
{
  color_text(GREEN);
  eprintf("[%s]\n",devicename);
  color_reset();
  if ( fds[device_id].fd != -1 ) // already open
    {
      color_text(MAGENTA);
      eprintf("=>Already opened.\n");
      color_reset();
      return 0;
    }
  fds[device_id].fd = open(devicename, O_RDWR | O_NONBLOCK);
  if ( fds[device_id].fd == -1 || fds[device_id].fd == NULL )
    {
      color_text(RED);
      eprintf("ERROR OPENING %s\n", devicename);
      color_reset();
      return 1;
    }
  if ( set_as_pty( fds[device_id].fd, baudrate) )
    {
      color_text(RED);
      eprintf("ERROR SET SERIAL %s\n", devicename);
      color_reset();
      return 1;
    }
  fds[device_id].events = POLLIN ;
  return 0;
}
/*  init all stream/device  */
int init_streams( char* serial_name, char* virtu_poly_name, char* virtu_printer_name)
{
  color_text(BLUE);
  eprintf("===>Open Device...\n");
  color_text(GREEN);
  /*  Serial  */
  if( init_stream(serial_name, serial) )
    {
      abandon_c("Error opening Serial ",8);
    }
  /*  Printer  */
  if(init_stream(virtu_printer_name, printer) )
    {
      abandon_c("Error opening VirtualPrinter Serial ",9);
    }
  /*  Poly  */
    if( init_stream(virtu_poly_name, poly) )
    {
      abandon_c("Error opening PolySoftware Serial ",10);
    }
  color_text(GREEN);
  eprintf("===>Ok. Done.\n");
  color_reset();
  return 1;
}

/*******************************************************/
/*   Well... The main...                               */
/*  1) handle arg                                      */
/*  2)  init streams                                   */
/*  3) loop                                            */
/*    3.1) wait for even on fds descriptos             */
/*    3.2) handle the event                            */
/*******************************************************/
int main(int argc, char* argv[])
{

  /* INIT. & VARS. */

  int timeout_msecs = 10;

  int ret;
  char serial_name[ARG_SIZE];
  char virtu_printer_name[ARG_SIZE];
  char virtu_poly_name[ARG_SIZE];
  int polyplexer_on = 1;
  char* pos;
  int data_state=0;

  /* Handle args  */
  if ( argc < 4 )
    {
      printf("Usage:  %s /serial/device /virtual/poly/pty /virtual/printer/pty\n\n", argv[0]);
      return 1;
    }
  /* Save device path/name */
  strncpy(serial_name, argv[1], ARG_SIZE);
  strncpy(virtu_poly_name,  argv[2], ARG_SIZE);
  strncpy(virtu_printer_name,  argv[3], ARG_SIZE);
  
  /* Init file descriptor with non-null value */
  int idx;
  for ( idx = 0; idx <FD_NUMBER ; ++idx)
    {
      fds[idx].fd = -1;
    }
  /* Open STREAMS device. */
  init_streams(serial_name, virtu_poly_name, virtu_printer_name);

  color_text(MAGENTA);
  eprintf("===> Start main loop server\n");
  color_reset();


  while ( polyplexer_on )
    {
      //      write( fds[serial].fd, "M105\n", 5 );
      ret = poll(fds, FD_NUMBER, timeout_msecs);
      
      if (ret > 0)
	{
	  /* An event on one of the fds has occurred. */
	  for (i=0; i<FD_NUMBER; i++)
	    {
	      /* INPUT ---- NEED TO READ    */
	      if (fds[i].revents & POLLIN) 
		{
		  data_state = read_stream(i);
		  if ( data_state == DATA_READY  )
		    {
		      if( i == printer )
			{
			  //eprintf("[printer]\n");
			  color_text(RED);
			  write( 1, input_buffer[printer], current_size[printer] );
			  color_reset();
			  write( fds[serial].fd, input_buffer[printer], current_size[printer]);
			  clear_stream(printer);
			}
		      else if( i == serial )
			{
			  //			  eprintf("[serial]\n");
			  pos = strchr( input_buffer[serial], '#'); /*  polybox data ?? */ /* CARE , check if the FULL data contain #, not only the begining... @todo */
			  if ( pos != NULL )
			    {
			      //  eprintf("=====> To Poly \n");
			      color_text(GREEN);
			      write( 1, input_buffer[serial], current_size[serial] );
			      color_reset();
			      write( fds[poly].fd, input_buffer[serial], current_size[serial] );
			    }
			  else /* rest for printer software == prevent add of of code. Since polybox code are always prefixed with # */ 
			    {
			      //  eprintf("=====> To Printer \n");
			      color_text(BLUE);
			      write( 1, input_buffer[serial], current_size[serial] );
			      color_reset();
			      write( fds[printer].fd, input_buffer[serial], current_size[serial] );
			    }
			  clear_stream(serial);
			}
		      else if( i == poly )
			{
			  //			  eprintf("[poly]\n");
			  color_text(YELLOW);
			  write( 1, input_buffer[poly], current_size[poly] );
			  color_reset();
			  write( fds[serial].fd, input_buffer[poly], current_size[poly] );
			  clear_stream(poly);
			}
		    }
		  else if( data_state == DATA_WAITING_MORE )
		    {
		      // write( 1, input_buffer[serial], current_size[serial] );
		      color_text(CYAN);
		      eprintf("   > Waiting...[%d]\n", current_size[i]);
		      color_reset();
		    }
		  else if ( data_state == DATA_CLOSED )
		    {
		      /*  reset fd descriptor */
		      fds[i].fd = -1;
		      /*  Process new init */
		      sleep(1); // wait a bit for socat to recreate file_descriptor
		      init_streams(serial_name, virtu_poly_name, virtu_printer_name);
		    }
		  else if ( data_state == DATA_NOTHING_NEW )
		    {
		      // eprintf("Nothing\n");
		    }
		  else if ( data_state == DATA_ERROR )
		    {
		      eprintf("DATA_ERROR\n");
		    }
		  else
		    eprintf("erff\n");
		}
	      else
		{
		  /*		  color_text(BLUE);*/
		  //		  eprintf("UnHandle event ! ...[ %d  %d %d %d %d %d  ]\n",fds[i].revents,POLLPRI , POLLRDNORM ,POLLERR  ,POLLHUP ,POLLNVAL );
		  /*		  color_reset();*/
		}
	    }
	}
      else if( ret < 0)
	{
	  perror("  poll() failed");
	  polyplexer_on = 0;
	}
      else if ( ret == 0 )
	{
	  // color_text(BLUE);
	  //eprintf("Listing...\n");
	  //color_reset();
	}
      
      
    }// end of while() loop
  color_text(BLUE);
  eprintf("BYE !\n");
  color_reset();
  return EXIT_SUCCESS;
}
