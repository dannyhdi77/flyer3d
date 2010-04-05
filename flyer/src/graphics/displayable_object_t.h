/*
 * displayable_object_t.h
 *
 *  Created on: 2010-04-03
 *      Author: krzychu
 */


#ifndef DISPLAYABLE_OBJECT_T_H_
#define DISPLAYABLE_OBJECT_T_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <vector3_t.h>
#include <model_t.h>
#include <matrix44_t.h>

//displayable object types definition
#define DISP_MODEL 1
#define DISP_CONE 2
#define DISP_LIGHT 3
#define DISP_TERRAIN 4
#define DISP_NONE 5

typedef struct{
	char type;	//type of object
	void *data;	//actual data
} displayable_object_t;

//initalizes object with specified data
void d_object_init(displayable_object_t*, void*);

//draw object
void d_object_display(displayable_object_t*);

#endif /* DISPLAYABLE_OBJECT_T_H_ */


