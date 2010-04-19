/*
 * pipe_t.c
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#include <pipe_t.h>

//as always, initalization
void pipe_init(pipe_t* p, int forward, int backward){
	body_init(&p->obj,p,DISP_PIPE);
}

//deletion
void pipe_delete(pipe_t* p){
	fifo_delete(&p->segments);
}

//refreshment
void pipe_refresh(pipe_t*, float dt, body_t* player_body);

//display pipe and all its segments
void pipe_display(pipe_t*);
