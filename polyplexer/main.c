

/******************************************************************
 *
 * @author: Skapin <skapinthefourb@gmail.com>
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
int baudrate = 115200;
int printer=2, poly=1, serial=0;
int i;


void abandon(char r[])
{
  perror(r);
  exit(EXIT_FAILURE);
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
/*  process serial event */
void handle_serial()
{
  int nbr_read=0;
  if (fds[i].revents & POLLIN) 
    {
      nbr_read = read( fds[serial].fd, input_buffer[serial], BUFFER_SIZE);
      if ( nbr_read > 0 )
	{
	  eprintf("[serial] {%s}\n",input_buffer[serial]);
			  
	  /* @todo We parse data . well..we will do it...soon  */
	  write( fds[serial].fd, input_buffer[serial], nbr_read);
	}
    }
}
/*  process prinetr event  */
void handle_printer()
{
  int nbr_read=0;
  /* INPUT ---- NEED TO READ    Printer -----> Serial       */
  if (fds[i].revents & POLLIN) 
    {
      nbr_read = read( fds[printer].fd, input_buffer[printer], BUFFER_SIZE);
      if ( nbr_read > 0 )
	{
	  
	  eprintf("[printer]\n");
	  eprintf("===> %s\n",input_buffer[printer]);
	  write( fds[serial].fd, input_buffer[printer], nbr_read);
	}
    }
}
/*  process polybox event */
void handle_poly()
{
  int nbr_read=0;
  if (fds[i].revents & POLLIN) 
    {
      nbr_read = read( fds[poly].fd, input_buffer[poly], BUFFER_SIZE);
      if ( nbr_read > 0 )
	{
	  eprintf("[poly]\n");
	  write( fds[serial].fd, input_buffer[poly], nbr_read);
	}
    }  
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
  fds[device_id].events = POLLIN;
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

  int timeout_msecs = 1000*3;

  int ret;
  char serial_name[ARG_SIZE];
  char virtu_printer_name[ARG_SIZE];
  char virtu_poly_name[ARG_SIZE];
  int polyplexer_on = 1;
  char hellocommand="Hello ! I'm PolyPlexer v0.4\n";

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
  write( fds[serial].fd, hellocommand, sizeof(hellocommand));

  while ( polyplexer_on )
    {
      ret = poll(fds, 2, timeout_msecs);
      
      if (ret > 0)
	{
	  /* An event on one of the fds has occurred. */
	  for (i=0; i<FD_NUMBER; i++)
	    {
	      /*  Reinit vars  */
	      memset(input_buffer, 0, sizeof(input_buffer));
	      /*   PRINTER FD  */
	      if( i == printer )
		{
		  handle_printer();
		}
	      /*   SERIAL FD    Serial ---------> Printer OR Poly (need parse)*/
	      else if( i == serial )
		{
		  handle_serial();
		}
	      /*   POLY FD  Poly -------> Serial */
	      else if( i == poly )
		{
		  handle_poly();
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
  return EXIT_SUCCESS;
}
