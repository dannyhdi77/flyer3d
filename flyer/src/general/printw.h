/*
 * printw.h
 *
 *  Created on: 2010-06-09
 *      Author: http://mycodelog.com/2010/03/23/printw/
 */

#ifndef PRINTW_H_
#define PRINTW_H_

#include <stdio.h>//&nbsp; Standard Input\Output C Library
#include <stdarg.h>//&nbsp; To use functions with variables arguments
#include <stdlib.h>//&nbsp; for malloc
#include <GL/glut.h>//&nbsp; Include GLUT, OpenGL, and GLU libraries

//  A pointer to a font style..
//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.

void printw (float x, float y, float z, float r, float g,float b,char* format, ...);

#endif /* PRINTW_H_ */
