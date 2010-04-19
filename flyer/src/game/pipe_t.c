/*
 * pipe_t.c
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#include <pipe_t.h>

//adds new random segment in front of pipe
void pipe_add_segment(pipe_t* p){
	segment_t new_segment;
	fifo_insert(&p->segments, &new_segment);
	segment_t* s = (segment_t*)fifo_get_front_pointer(&p->segments);
	if(fifo_size(&p->segments) > 1){
		//not first segment, we do necessary randomization
		body_rotate(&s->obj, B_UP, random_range(-1.0, 1.0));
	}
}

//as always, initalization
void pipe_init(pipe_t* p, int forward, int backward){
	body_init(&p->obj);
	fifo_init(&p->segments,sizeof(segment_t), PIPE_MAX_LENGTH);

	//we assume that player is placed in the middle segment
	//first, add back segments and middle segment

}

//deletion
void pipe_delete(pipe_t* p){
	fifo_delete(&p->segments);
}

//refreshment
void pipe_refresh(pipe_t* p, float dt, body_t* player_body){

}

//display pipe and all its segments
void pipe_display(pipe_t* p){
	glPushMatrix();
	body_apply_transform(&p->obj);
	//print all segments
	glPopMatrix();
}
