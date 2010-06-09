/*
 * pipe_t.c
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#include <pipe_t.h>

//adds new random segment in front of pipe
void pipe_add_segment(pipe_t* p){
	//create new segment and add it to the queue
	segment_t new_segment;
	segment_t* last = (segment_t*)fifo_get_front_pointer(&p->segments);	//points to segment right behind
	segment_t* s = &new_segment;//(segment_t*)fifo_get_front_pointer(&p->segments);

	//initalize it
	segment_init(s, random_range(PIPE_MIN_SEGMENT_LENGTH, PIPE_MAX_SEGMENT_LENGTH));
	vector3_set(s->color,random_range(0.7,1.0),random_range(0.0,0.3),random_range(0.0,0.3));

	if(fifo_size(&p->segments) > 0){
		//we create connector
		segment_t connector;
		segment_init_connector(&connector, last, s,
				random_range(PIPE_MIN_UP_ROTATION, PIPE_MAX_UP_ROTATION),
				random_range(PIPE_MIN_OUT_ROTATION, PIPE_MAX_OUT_ROTATION)
		);

		//not first segment, we do necessary position randomization
		s->obj = last->obj; //copy position and orientation
		body_move_forward(&s->obj, -last->length - PIPE_GAP);
		body_rotate(&s->obj, B_UP, connector.up_rotation);
		body_rotate(&s->obj, B_OUT, connector.out_rotation);

		fifo_insert(&p->segments, &connector);
	}
	fifo_insert(&p->segments, s);
}

//as always, initalization
void pipe_init(pipe_t* p, int forward){
	p->forward = forward;
	body_init(&p->obj);
	fifo_init(&p->segments,sizeof(segment_t), 2*PIPE_MAX_LENGTH);
	//first segments
	int i;
	for(i=0; i<=p->forward ; i++)
		pipe_add_segment(p);

}

//deletion
void pipe_delete(pipe_t* p){
	fifo_delete(&p->segments);
}

//refreshment
void pipe_refresh(pipe_t* p, float dt, body_t* player_body){
	segment_t* last = (segment_t*)fifo_get_back_pointer(&p->segments);
	if(!segment_in(last, player_body->position)){
		//if last segment was normal, add new in front
		if(last->type == SEGMENT_NORMAL)
			pipe_add_segment(p);
		//player escaped last segment, time to remove it
		fifo_get(&p->segments, NULL);
	}
}

//display pipe and all its segments
void pipe_display(pipe_t* p){
	glPushMatrix();
	body_apply_transform(&p->obj);
	//print all segments
	fifo_iterate(&p->segments,segment_display,NULL);
	glPopMatrix();
}

int pipe_collision(pipe_t* p, vector3_t point){
	struct collision_s col;
	vector3_set_v(col.point, point);
	col.collides = 0;
	fifo_iterate(&p->segments,segment_collide,&col);
	return col.collides;
}
