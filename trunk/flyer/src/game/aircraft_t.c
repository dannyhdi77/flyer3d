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
	vector3_set(a->object.velocity,0.0,0.0, -2.0);
	vector3_set(a->object.position, 0.0, 0.0,-20.0);

	//linear
	vector3_set(a->gravity,0.0, -1.0, 0.0);
	a->drag_coeff = 100.0;
	a->lift_coeff = 1.0;
	a->mass = 20.0;
	a->thrust = -200.0;

	//angular
	a->up_coeff = 3.0;
	a->forward_coeff = 5.0;
	a->out_coeff = 3.0;
}


//refreshes aircrafts state
void aircraft_refresh(aircraft_t* a, float dt){
	//linear
	//calculate resulting force
	vector3_t f_result, f_term;
	vector3_set(f_result, 0.0, 0.0, 0.0);

	//calculate gravity
	vector3_set_v(f_term, a->gravity);
	vector3_scale(f_term, a->mass);
	vector3_add(f_result, f_term);

	//calculate thrust vector
	vector3_set_v(f_term, a->object.forward);
	vector3_scale(f_term, a->thrust);
	vector3_add(f_result, f_term);

	float speed = vector3_length(a->object.velocity);
	speed *= speed;


	//calculate lift force
	vector3_set_v(f_term, a->object.up);
	vector3_scale(f_term, a->lift_coeff*speed);
	vector3_add(f_result, f_term);

	//calculate drag force
	vector3_set_v(f_term, a->object.velocity);
	vector3_normalize(f_term);
	vector3_scale(f_term, -a->drag_coeff*speed);
	vector3_add(f_result, f_term);

	//calculate acceleration
	vector3_scale(f_result, 1.0/a->mass);

	//apply it to a body
	vector3_set_v(a->object.acceleration, f_result);

	//angular
	a->object.up_v = a->tail*speed*a->up_coeff;
	a->object.forward_v = a->ailerons*speed*a->forward_coeff;
	a->object.out_v = a->elevator*speed*a->out_coeff;

	body_do_kinematics(&a->object, dt);
}
