/*
 * aircraft_t.h
 *
 *  Created on: 2010-04-12
 *      Author: krzychu
 */

#ifndef AIRCRAFT_T_H_
#define AIRCRAFT_T_H_

#include <body_t.h>
#include <renderer_t.h>
#include <vector3_t.h>

#define A_ACTIVE 1
#define A_INACTIVE 2

typedef struct{
	body_t object;

	float mass; //object mass
	vector3_t gravity;	//vector of gravity acceleration

	//linear movement coeffs
	float drag_coeff;
	float lift_coeff;

	//indicate if steers are in use, and how far are they from
	//their balance position
	float ailerons;
	float elevator;
	float tail;

	//angular movement coefficients
	float up_coeff;
	float forward_coeff;
	float out_coeff;

	float thrust;

} aircraft_t;

//initalizes aircraft structure with its model
void aircraft_init(aircraft_t*, model_t*);

//deletes aircraft
void aircraft_delete(aircraft_t*);

//loads test settings
void aircraft_load_test_settings(aircraft_t*);

//displays aircraft
void aircraft_display(aircraft_t*, renderer_t*);

//refreshes aircrafts state
void aircraft_refresh(aircraft_t*, float);


#endif /* AIRCRAFT_T_H_ */
