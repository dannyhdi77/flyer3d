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
	vector3_set(b->position, 0.0, 0.0, 0.0);
	vector3_set(b->forward, 1.0, 0.0, 0.0);
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
	vector3_invert(b->position);
	vector3_invert(b->up);
	vector3_invert(b->forward);
}

//apply inverted object transform
void body_apply_inverted_transform(body_t* b){
	body_frame_invert(b);
	body_apply_transform(b);
	body_frame_invert(b);	//back to normal state
}

//sets body position
void body_set_position(body_t* b, vector3_t v){
	vector3_set(b->position, v[0], v[1], v[2]);
}

//rotates body around given axis, angle in radians
void body_rotate(body_t* b, char axis, float angle){
	if(axis == B_FORWARD){
		vector3_rotate(b->up, b->forward, angle);
	}
	else if(axis == B_UP){
		vector3_rotate(b->forward, b->up, angle);
	}
	else{
		vector3_t out;
		vector3_cross_product(out, b->up, b->forward);
		vector3_rotate(b->forward, out, angle);
		vector3_rotate(b->up, out, angle);
	}
	vector3_normalize(b->forward);
	printf("%f %f %f\n", b->forward[0], b->forward[1], b->forward[2]);
	vector3_normalize(b->up);
}

//moves body forward
void body_move_forward(body_t* b, float x){
	vector3_t dx;
	vector3_set_v(dx, b->forward);
	vector3_scale(dx, x);
	vector3_add(b->position, dx);
}
