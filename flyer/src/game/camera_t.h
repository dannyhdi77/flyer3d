/*
 * camera_t.h
 *
 *  Created on: 2010-04-14
 *      Author: krzychu
 */

#ifndef CAMERA_T_H_
#define CAMERA_T_H_

#include <body_t.h>

#define CAMERA_FIXED 1	//camera stays at its inital position
#define CAMERA_GLUED 2		//camera is at fixed positon to followed object
#define CAMERA_DYNAMIC 3	//camera behaves like helicopter
#define CAMERA_FIXED_ANGLES 4 //camera keeps angles, bt is able to move

#define MAX_DELAY 100

typedef struct{
	body_t obj;

	//object which camera follows
	body_t* subject;

	//vector of relative camera position
	vector3_t relatve_pos;

	//camera mode
	int mode;

	//queries storing orientations in dynamic mode


} camera_t;

//initalizes camera with body to follow and mode
void camera_init(camera_t*, body_t *, int);

//set relative position
void camera_set_relative(camera_t*, vector3_t);

//refreshes camera position
void camera_refresh(camera_t*, float);


#endif /* CAMERA_T_H_ */
