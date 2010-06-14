/*
 * fire_t.h
 *
 *  Created on: 2010-06-09
 *      Author: krzychu
 */

#ifndef FIRE_T_H_
#define FIRE_T_H_

#define PARTICLE_SPEED 2000
#define MAX_PARTICLES 1000
#define FIRE_PARTICLE_SIZE 0.1
#define FIRE_X_SIZE 0.5
#define FIRE_Y_SIZE 0.5

#define FIRE_X_STEP 1
#define FIRE_Y_STEP 1
#define FIRE_Z_STEP 3

#define FIRE_PROBABILITY 0.5
#define FIRE_NEW_RATE 100
#define FIRE_LENGTH 10.0


#include <vector3_t.h>
#include <GL/glew.h>
#include <fifo_t.h>
#include <body_t.h>
#include <stdlib.h>
#include <utilties.h>

typedef struct {
	vector3_t position;
	int color_index ;
} particle_t;

typedef struct {
	fifo_t particles;
	body_t object;
	float normal_direction; //z coordinate of each point normal
	vector3_t palette[256];
} fire_t;


void fire_init(fire_t*);

void fire_delete(fire_t*);

void fire_refresh(fire_t*, float dt);

void fire_display(fire_t*);

#endif /* FIRE_T_H_ */
