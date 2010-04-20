/*
 * pipe_t.h
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#ifndef PIPE_T_H_
#define PIPE_T_H_

#include <fifo_t.h>
#include <body_t.h>
#include <segment_t.h>
#include <utilties.h>

#define PIPE_MAX_LENGTH 10
#define PIPE_MAX_SEGMENT_LENGTH 100.0
#define PIPE_MIN_SEGMENT_LENGTH 50.0

#define PIPE_MIN_UP_ROTATION -0.5
#define PIPE_MAX_UP_ROTATION 0.5
#define PIPE_MIN_OUT_ROTATION -0.5
#define PIPE_MAX_OUT_ROTATION 0.5

#define PIPE_GAP SEGMENT_GAP


typedef struct {
	//pipe position and orientation
	body_t obj;

	//fifo with pipe segments
	fifo_t segments;

	int forward;	//how many segments should be kept in front of player

} pipe_t;

//as always, initalization
void pipe_init(pipe_t*, int forward);

//deletion
void pipe_delete(pipe_t*);

//refreshment
void pipe_refresh(pipe_t*, float dt, body_t* player_body);

//display pipe and all its segments
void pipe_display(pipe_t*);

#endif /* PIPE_T_H_ */
