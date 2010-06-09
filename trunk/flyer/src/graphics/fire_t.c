/*
 * fire_t.c
 *
 *  Created on: 2010-06-09
 *      Author: krzychu
 */

#include <fire_t.h>

void particle_init(particle_t* p,float x, float y){
	vector3_set(p->position,x,y,0.0);
}

void particle_randomize(particle_t* p, float* dt){
	p->position[0] += (*dt)*random_range(-FIRE_X_STEP, FIRE_X_STEP);
	p->position[1] += (*dt)*random_range(-FIRE_Y_STEP, FIRE_Y_STEP);
	p->position[2] += (*dt)*random_range(0, FIRE_Z_STEP);
}

void particle_display(particle_t* p, vector3_t* palette){
	int color_index = (p->position[2]/FIRE_LENGTH)*255;
	color_index += random_range(0.0,10.0);
	if(color_index > 255){
		color_index = 255;
	}
	glColor3f(palette[color_index][0],palette[color_index][1],palette[color_index][2]);
	glVertex3f(p->position[0],p->position[1],p->position[2]);
}

void fire_init(fire_t* f){
	fifo_init(&f->particles,sizeof(particle_t),MAX_PARTICLES);
	body_init(&f->object);

	//Initialize palette
	int i;
	for(i=0;i<128;i++)
		vector3_set(f->palette[i],i*2,i,2);
	for(i=0;i<64;i++)
		vector3_set(f->palette[i+128],254,i+127,i+2);
	for(i=0;i<66;i++)
		vector3_set(f->palette[i+190],254,i+190,i+65);
	vector3_set(f->palette[255],255,255,132);

	for(i=0; i<256 ; i++)
		vector3_scale(f->palette[i], 1.0/255.0);
}

void fire_delete(fire_t* f){
	fifo_delete(&f->particles);
}

void fire_refresh(fire_t* f, float dt){
	//randomize particles
	fifo_iterate(&f->particles,&particle_randomize,&dt);

	//do we need to add new particles?
	int i, loops, n_new = 0;
	loops = dt*FIRE_NEW_RATE;
	for(i=0;i<loops; i++){
		if(random_range(0.0,1.0) < FIRE_PROBABILITY){
			//particle new
			n_new++;
			particle_t newp;
			particle_init(&newp,random_range(-FIRE_X_SIZE,FIRE_X_SIZE),
					random_range(-FIRE_Y_SIZE,FIRE_Y_SIZE));
			fifo_insert(&f->particles, &newp);
		}
	}
	//do we need to delete one ?
	i=0;
	while(fifo_size(&f->particles) >= MAX_PARTICLES - n_new){
		fifo_get(&f->particles, NULL);
	}
}

void fire_display(fire_t* f){
	glColor3f(1.0,0.0,0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glNormal3f(0.0,0.0,-1.0);
	fifo_iterate(&f->particles,&particle_display,f->palette);
	glEnd();
}
