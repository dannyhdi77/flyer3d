/*
 * printw.c
 *
 *  Created on: 2010-06-09
 *      Author: krzychu
 */

#include <printw.h>

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void printw (float x, float y, float z, float r, float g,float b,char* format, ...){
	GLvoid *font_style =  GLUT_BITMAP_TIMES_ROMAN_24;

	va_list args;   //  Variable argument list
    int i;          //  Iterator

    //  Initialize a variable argument list
    va_start(args, format);

    //  Return the number of characters in the string referenced the list of arguments.
    // _vscprintf doesn't count terminating '\0' (that's why +1)
    char buffer[1000];


    //  Write formatted output using a pointer to the list of arguments
    vsprintf(buffer, format, args);

    //  End using variable argument list
    va_end(args);

    //  Set proper drawing color
    glColor3f(r,g,b);

    //  Specify the raster position for pixel operations.
    glRasterPos3f (x, y, z);

    //  Draw the characters one by one
    for (i = 0; buffer[i] != '\0'; i++)
    glutBitmapCharacter(font_style, buffer[i]);


}
