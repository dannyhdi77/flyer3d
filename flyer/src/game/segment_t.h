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

//settings for all segments
#define SEGMENT_N_POINTS 100.0
#define SEGMENT_RADIUS 10

typedef struct {
	//segments position and orientation
	body_t obj;

	float length;

	//segments color
	vector3_t color;
} segment_t;

//sets some basic properties
void segment_init(segment_t*, float length);

//deletes segment
void segment_delete(segment_t*);

//prints segment
void segment_display(segment_t*);

//pysics and so
void segment_refresh(segment_t*, float dt);

#endif /* SEGMENT_T_H_ */
