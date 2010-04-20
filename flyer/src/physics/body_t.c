/*
 * body_t.c
 *
 *  Created on: 2010-04-04
 *      Author: krzychu
 */
#include <body_t.h>

//boring initalization
void body_init(body_t* b){
	vector3_set(b->position, 0.0, 0.0, 0.0);
	vector3_set(b->forward, 0.0, 0.0, 1.0);
	vector3_set(b->up, 0.0, 1.0, 0.0);

	vector3_set(b->velocity, 0.0, 0.0, 0.0);
	vector3_set(b->acceleration, 0.0, 0.0, 0.0);

	b->up_v = 0.0;
	b->forward_v = 0.0;
	b->out_v = 0.0;

	b->up_a = 0.0;
	b->forward_a = 0.0;
	b->out_a = 0.0;
}

//retrieves body transformation matrix
void body_get_transformation_matrix(body_t* obj, matrix44_t result){
	//compute x axis vector
	vector3_t x_axis;
	vector3_cross_product(x_axis, obj->up, obj->forward);

	//create transform matrix, its a little bit too complicated to explain it here
	matrix44_compose(result, x_axis, 0.0, obj->up, 0.0, obj->forward, 0.0, obj->position, 1.0);
}

//retrieves inverted body transformation matrix
void body_get_inverted_transformation_matrix(body_t* obj, matrix44_t transform){
	//compute x axis vector
	vector3_t x_axis;
	vector3_cross_product(x_axis, obj->up, obj->forward);

	//create and apply transform matrix, but this time transposed
	matrix44_set_row(transform, 0, x_axis, 0.0);
	matrix44_set_row(transform, 1, obj->up, 0.0);
	matrix44_set_row(transform, 2, obj->forward, 0.0);
	//last row
	transform[3] = 0.0;
	transform[7] = 0.0;
	transform[11] = 0.0;
	transform[15] = 1.0;

	matrix44_t tmp;
	vector3_t tmp_v;
	vector3_set_v(tmp_v,obj->position);
	vector3_invert(tmp_v);
	matrix44_identity(tmp);
	matrix44_set_column(tmp,3,tmp_v,1.0);

	matrix44_mul(transform, tmp);
}

//transforms vector into body space
void body_transform_vector(body_t* obj, vector3_t v){
	matrix44_t inv;
	body_get_inverted_transformation_matrix(obj, inv);
	matrix44_mul_vector(inv, v);
}

//apply object transform, second argument is renderer structure
void body_apply_transform(body_t* obj){
	matrix44_t transform;
	body_get_transformation_matrix(obj, transform);
	glMultMatrixf(transform);
}


//needed by inverted transform, simply invertes vectors
void body_frame_invert(body_t* b){
	vector3_invert(b->position);
	vector3_invert(b->up);
	vector3_invert(b->forward);
}

//apply inverted object transform
void body_apply_inverted_transform(body_t* obj){
	//create and apply transform matrix, but this time transposed
	matrix44_t transform;
	body_get_inverted_transformation_matrix(obj, transform);
	glMultMatrixf(transform);
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
	vector3_normalize(b->up);
}

//moves body forward
void body_move_forward(body_t* b, float x){
	vector3_t dx;
	vector3_set_v(dx, b->forward);
	vector3_scale(dx, x);
	vector3_add(b->position, dx);
}

//calculates both linear and angular displacements in time dt
void body_do_kinematics(body_t* b, float dt){
	//move object
	vector3_t displacement;
	vector3_set_v(displacement, b->velocity);
	vector3_scale(displacement, dt);
	vector3_add(b->position, displacement);

	//change its speed
	vector3_t dv;
	vector3_set_v(dv, b->acceleration);
	vector3_scale(dv, dt);
	vector3_add(b->velocity,dv);

	//do all rotations
	body_rotate(b,B_UP,b->up_v*dt);
	body_rotate(b,B_FORWARD,b->forward_v*dt);
	body_rotate(b,B_OUT,b->out_v*dt);

	//modify rotation speeds
	b->up_v += dt*b->up_a;
	b->forward_v += dt*b->forward_a;
	b->out_v += dt*b->out_a;
}
