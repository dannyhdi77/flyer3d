/*
 * aircraft_t.c
 *
 *  Created on: 2010-04-12
 *      Author: krzychu
 */
#include <aircraft_t.h>

//initalizes aircraft structure with its model
void aircraft_init(aircraft_t* a, model_t* m){
	body_init(&a->object);
	a->model = m;

	a->ailerons = 0.0;
	a->elevator = 0.0;
	a->tail = 0.0;

}

//deletes aircraft
void aircraft_delete(aircraft_t* a){
	;
}

//draws aircraft
void aircraft_display(aircraft_t* a){
	glPushMatrix();
		body_apply_transform(&a->object);
		model_display(a->model);
	glPopMatrix();
}

//loads test settings
void aircraft_load_test_settings(aircraft_t* a){
	vector3_set(a->object.position, 0.0, 0.0,0.0);
	//angular
	a->up_coeff = 3.0;
	a->forward_coeff = 5.0;
	a->out_coeff = 3.0;

	a->speed = 5.0;
}


//refreshes aircrafts state
void aircraft_refresh(aircraft_t* a, float dt){
	vector3_set_v(a->object.velocity, a->object.forward);
	vector3_scale(a->object.velocity, -a->speed);

	//angular
	a->object.up_v = a->tail*a->up_coeff*a->speed;
	a->object.forward_v = a->ailerons*a->forward_coeff*a->speed;
	a->object.out_v = a->elevator*a->out_coeff*a->speed;

	body_do_kinematics(&a->object, dt);
}
