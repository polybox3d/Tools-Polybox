#ifndef COLOR_H
#define COLOR_H
/**
 * @file Color.h
 * @author : SkapiN <skapinthefourb@gmail.com>
 * 
 * Allow color output for stdin terminal
 *
 **/
#include <stdio.h>
#include <stdlib.h>

#define RESET		0
#define BRIGHT 		1
#define DIM		2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7



void textcolor(int attr, int fg, int bg);
void color_reset();

void color_text(int fg);
#endif
