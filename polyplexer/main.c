

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

#ifndef VERBOSE 
 #define VERBOSE 0
#else
 #define VERBOSE 1
#endif

/*  Debug printf to stderr.   */
#define eprintf(fmt, ...) \
            do { if (VERBOSE) fprintf (stderr, fmt, ##__VA_ARGS__) ; } while (0)

/*  Globals Vars. */
struct pollfd fds[FD_NUMBER];
char input_buffer[FD_NUMBER][BUFFER_SIZE];
char tmp_buffer[BUFFER_SIZE];
int current_size[FD_NUMBER]={0,0,0};
int baudrate = 115200;
//int baudrate = 9600;
int printer=2, poly=1, serial=0;
int i;

void abandon(char r[])
{
  perror(r);
  exit(EXIT_FAILURE);
}

void clear_stream(int fd_id)
{
  memset(input_buffer[fd_id], 0, sizeof(input_buffer[fd_id]));
  current_size[fd_id] = 0;
}

/*  Define a fd as a pty/serial file with a given baudrate.  */
void set_as_pty(int fd, int baudrate)
{
  /* serial port parameters */
  struct termios newtio;
  memset(&newtio, 0, sizeof(newtio));
  struct termios oldtio;
  tcgetattr(fd, &oldtio);

  newtio = oldtio;
  newtio.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = 0;
  newtio.c_oflag = 0;
  newtio.c_lflag = 0;
  newtio.c_cc[VMIN] = 1;
  newtio.c_cc[VTIME] = 0;
  tcflush(fd, TCIFLUSH);

  cfsetispeed(&newtio, baudrate);
  cfsetospeed(&newtio, baudrate);
  tcsetattr(fd, TCSANOW, &newtio);

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
	  char* pos = strchr( tmp_buffer,'\r');
	  char* pos2 = strchr( tmp_buffer,'\n');
	  if ( pos != NULL  || pos2 != NULL ) /* end found  */
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
  return DATA_NOTHING_NEW;
}

/*  open a given device and store it inside fds struct */
int init_stream(char* devicename, int device_id)
{
  eprintf("[%s]\n",devicename);
  fds[device_id].fd = open(devicename, O_RDWR);
  if ( fds[device_id].fd == -1 || fds[device_id].fd == NULL )
    {
      color_text(RED);
      eprintf("ERROR OPENING %s\n", devicename);
      color_reset();
      return 1;
    }
  set_as_pty( fds[device_id].fd, baudrate);
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
      abandon("Error: ");
    }
  /*  Printer  */
  if(init_stream(virtu_printer_name, printer) )
    {
      abandon("Error: ");
    }
  /*  Poly  */
    if( init_stream(virtu_poly_name, poly) )
    {
      abandon("Error: ");
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

  int timeout_msecs = 1000;

  int ret;
  char serial_name[ARG_SIZE];
  char virtu_printer_name[ARG_SIZE];
  char virtu_poly_name[ARG_SIZE];
  int polyplexer_on = 1;
  char hellocommand[]="Hello ! I'm PolyPlexer v0.4\n";
  char* pos;
  int data_state=0;

  /* Handle args  */
  if ( argc < 4 )
    {
      printf("Usage:  %s /serial/device /virtual/poly/pty /virtual/printer/pty\n\n", argv[0]);
      return EXIT_FAILURE;
    }
  /* Save device path/name */
  strncpy(serial_name, argv[1], ARG_SIZE);
  strncpy(virtu_poly_name,  argv[2], ARG_SIZE);
  strncpy(virtu_printer_name,  argv[3], ARG_SIZE);
  

  /* Open STREAMS device. */
  init_streams(serial_name, virtu_poly_name, virtu_printer_name);

  
  color_text(MAGENTA);
  eprintf("===> Start main loop server\n");
  color_reset();

  /* We say HELLO ! Cause we are nice :p (and because we dont want binary stream FFS ! */
  //  write( fds[serial].fd, hellocommand, sizeof(hellocommand));
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
			  eprintf("[printer]\n");
			  write( fds[serial].fd, input_buffer[printer], current_size[printer]);
			  clear_stream(printer);
			}
		      else if( i == serial )
			{
			  eprintf("[serial]\n");
			  pos = strchr( input_buffer[serial], '#'); /*  polybox data ?? */ /* CARE , check if the FULL data contain #, not only the begining... @todo */
			  if ( pos != NULL )
			    {
			      eprintf("=====> To Poly \n");
			      write( fds[poly].fd, input_buffer[serial], current_size[serial] );
			    }
			  else /* rest for printer software == prevent add of of code. Since polybox code are always prefixed with # */ 
			    {
			      eprintf("=====> To Printer \n");
			      write( fds[printer].fd, input_buffer[serial], current_size[serial] );
			    }
			  clear_stream(serial);
			}
		      else if( i == poly )
			{
			  eprintf("[poly]\n");
			  write( fds[serial].fd, input_buffer[poly], current_size[poly] );
			  clear_stream(poly);
			}
		    }
		  else if( data_state == DATA_WAITING_MORE )
		    {
		      eprintf("waiting...%d\n",current_size[i]);
		    }
		  else if ( data_state == DATA_NOTHING_NEW )
		    {
		      eprintf("nothin\n");
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
	  color_text(BLUE);
	  eprintf("Listing...\n");
	  color_reset();
	}
      
      
    }// end of while() loop
  color_text(BLUE);
  eprintf("BYE !\n");
  color_reset();
  return EXIT_SUCCESS;
}
