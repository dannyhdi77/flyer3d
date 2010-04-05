/*
 * body_t.c
 *
 *  Created on: 2010-04-04
 *      Author: krzychu
 */
#include <body_t.h>

//boring initalization
void body_init(body_t* b, void* data, char type){
	b->model.data = data;
	b->model.type = type;
	b->x_angle = 0.0;
	b->y_angle = 0.0;
	vector3_set(b->position, 0.0, 0.0, 0.0);
	vector3_set(b->forward, 0.0, 0.0, 1.0);
	vector3_set(b->up, 0.0, 1.0, 0.0);
}

//apply object transform, second argument is renderer structure
void body_apply_transform(body_t* obj){
	//compute x axis vector
	vector3_t x_axis;
	vector3_cross_product(x_axis, obj->up, obj->forward);

	//create and apply transform matrix, its a little bit too complicated to explain it here
	matrix44_t transform;
	matrix44_compose(transform, x_axis, 0.0, obj->up, 0.0, obj->forward, 0.0, obj->position, 1.0);
	glMultMatrixf(transform);
}

//needed by inverted transform, simply invertes vectors
void body_frame_invert(body_t* b){
	vector3_invert(&b->position);
	vector3_invert(&b->up);
	vector3_invert(&b->forward);
}

//apply inverted object transform
void body_apply_inverted_transform(body_t* b){
	body_frame_invert(b);
	body_apply_transform(b);
	body_frame_invert(b);	//back to normal state
}

//sets body position
void body_set_position(body_t* b, vector3_t v){
	vector3_set(&b->position, v[0], v[1], v[2]);
}
