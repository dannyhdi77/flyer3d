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

//displayable object types definition
#define DISP_MODEL 1
#define DISP_CONE 2
#define DISP_LIGHT 3

typedef struct{
	char type;	//type of object
	vector3_t position;	 //position of object
	vector3_t up;	//vector pointing up from the object
	vector3_t forward;	//vector pointing forward, both for orientation

	//temporary
	float x_angle;
	float y_angle;

	void *data;	//actual data
} displayable_object_t;

//initalizes object with specified data
void d_object_init(displayable_object_t*, void*);

//apply object transform, second argument is renderer structure
void d_object_apply_transform(displayable_object_t*, void* r);

//draw object
void d_object_display(displayable_object_t*, void* r);

#endif /* DISPLAYABLE_OBJECT_T_H_ */


