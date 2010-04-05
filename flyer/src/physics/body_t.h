/*
 * body_t.h
 *
 *  Created on: 2010-04-04
 *      Author: krzychu
 */

#ifndef BODY_T_H_
#define BODY_T_H_

#include <displayable_object_t.h>
#include <vector3_t.h>
#include <matrix44_t.h>

typedef struct {
	displayable_object_t model;	//3d model of body

	vector3_t position;	 //position of object
	vector3_t up;	//vector pointing up from the object
	vector3_t forward;	//vector pointing forward, both for orientation

	//temporary
	float x_angle;
	float y_angle;
} body_t;

//boring initalization
void body_init(body_t*, void*, char);

//sets body position
void body_set_position(body_t*, vector3_t);

//apply object transform
void body_apply_transform(body_t*);

//apply inverted object transform
void body_apply_inverted_transform(body_t*);

#endif /* BODY_T_H_ */
