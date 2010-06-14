/*
 * body_t.h
 *
 *  Created on: 2010-04-04
 *      Author: krzychu
 */

#ifndef BODY_T_H_
#define BODY_T_H_

#include <vector3_t.h>
#include <matrix44_t.h>
#include <GL/glew.h>
#include <SDL/SDL.h>

typedef struct {
	vector3_t position;	 //position of object
	vector3_t up;	//vector pointing up from the object
	vector3_t forward;	//vector pointing forward, both for orientation

	vector3_t velocity;		//object linear velocity vector
	vector3_t acceleration;	//object linear acceleration vector

	float up_v;		//rotation speed around up vector
	float forward_v;	//rotation sped around forward vector
	float out_v;	//rotation speed around out vector

	float up_a;		//rotation speed around up vector
	float forward_a;	//rotation sped around forward vector
	float out_a;	//rotation speed around out vector

} body_t;

//boring initalization
void body_init(body_t*);

//sets body position
void body_set_position(body_t*, vector3_t);

//retrieves body transformation matrix
void body_get_transformation_matrix(body_t*, matrix44_t reslut);

//retrieves inverted body transformation matrix
void body_get_inverted_transformation_matrix(body_t*, matrix44_t reslut);

//transforms vector into body space
void body_transform_vector(body_t*, vector3_t);

//apply object transform
void body_apply_transform(body_t*);

//apply inverted object transform
void body_apply_inverted_transform(body_t*);

//rotates body around given axis, angle in radians
#define B_FORWARD 1
#define B_UP 2
#define B_OUT 3
void body_rotate(body_t* b, char axis, float angle);

//moves body forward
void body_move_forward(body_t*, float);

//calculates both linear and angular displacements in time dt
void body_do_kinematics(body_t*, float dt);

#endif /* BODY_T_H_ */
