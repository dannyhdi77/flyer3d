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
#define SEGMENT_HOLD 50.0

//segment types
#define SEGMENT_NORMAL 1
#define SEGMENT_CONNECTOR 2

typedef struct {
	//segment type, straight or connector
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

	//handle of texture for this segment
	int texture;
} segment_t;

//structure that holds collision check and its result
struct collision_s{
	int collides;
	vector3_t point;
};

//sets some basic properties
void segment_init(segment_t*, float length, int texture_index);

//initalizes segment as connector beetween two normal segments
void segment_init_connector(segment_t*, segment_t* prev, segment_t* next, float upr, float outr);

//deletes segment
void segment_delete(segment_t*);

//prints segment
void segment_display(segment_t*, void*);

//pysics and so
void segment_refresh(segment_t*, float dt);

//returns 1 if point is inside segment
int segment_in(segment_t* s, vector3_t v);

//returns 1 if point collides with segment
void segment_collide(segment_t *s, struct collision_s*);

#endif /* SEGMENT_T_H_ */
