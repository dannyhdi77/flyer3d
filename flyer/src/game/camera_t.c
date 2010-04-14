/*
 * camera_t.c
 *
 *  Created on: 2010-04-14
 *      Author: krzychu
 */

#include <camera_t.h>

//initalizes camera with body to follow
void camera_init(camera_t* c , body_t *b, int mode){
	c->mode = mode;
	c->subject = b;
	body_init(&c->obj, NULL, DISP_NONE);
	//default camera position
	vector3_set(c->relatve_pos, 0.0, 2.0, 15.0);
}

//set relative position
void camera_set_relative(camera_t* c, vector3_t v){
	vector3_set_v(c->relatve_pos,v);
}

//refreshes camera position
void camera_refresh(camera_t* c, float dt){
	if(c->mode == CAMERA_FIXED_ANGLES){
		vector3_set_v(c->obj.position, c->subject->position);
		vector3_add(c->obj.position, c->relatve_pos);
		vector3_print(c->obj.position);
	}
	else if(c->mode == CAMERA_GLUED){
		//copy angular vals
		vector3_set_v(c->obj.forward, c->subject->forward);
		vector3_set_v(c->obj.up, c->subject->up);

		//linear translation
		vector3_t term;
		vector3_set_v(c->obj.position, c->subject->position);

		vector3_set_v(term,c->subject->forward);
		vector3_scale(term,c->relatve_pos[2]);
		vector3_add(c->obj.position, term);

		vector3_set_v(term,c->subject->up);
		vector3_scale(term,c->relatve_pos[1]);
		vector3_add(c->obj.position, term);

		vector3_cross_product(term,c->subject->up, c->subject->forward);
		vector3_scale(term,c->relatve_pos[0]);
		vector3_add(c->obj.position, term);
	}
}
