/*
 * pipe_t.h
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#ifndef SEGMENT_T_H_
#define SEGMENT_T_H_

#include <body_t.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

//settings for all segments
#define SEGMENT_N_POINTS 100.0
#define SEGMENT_RADIUS 10
#define SEGMENT_GAP 10.0

//segment types
#define SEGMENT_NORMAL 1
#define SEGMENT_CONNECTOR 2

typedef struct {
	//segment type, true or connector
	int type;

	//segment position and orientation
	body_t obj;


	//segment color
	vector3_t color;
	vector3_t next_color;	//used for connectors

	//length
	float length;

	//rotation relative to previous segment used for connectors
	float up_rotation, out_rotation;

} segment_t;

//sets some basic properties
void segment_init(segment_t*, float length);

//initalizes segment as connector beetween two normal segments
void segment_init_connector(segment_t*, segment_t* prev, segment_t* next, float upr, float outr);

//deletes segment
void segment_delete(segment_t*);

//prints segment
void segment_display(segment_t*);

//pysics and so
void segment_refresh(segment_t*, float dt);

#endif /* SEGMENT_T_H_ */
