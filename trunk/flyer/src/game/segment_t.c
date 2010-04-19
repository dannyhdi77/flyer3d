/*
 * segment_t.c
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#include <segment_t.h>

//sets some basic properties
void segment_init(segment_t* s, float length){
	body_init(&s->obj, s, DISP_SEGMENT);
	s->length = length;
}

//deletes segment
void segment_delete(segment_t* s){
	//do nothing
}

//prints segment
void segment_display(segment_t* s){
	int i;
	float angle_step = 2*3.1415/SEGMENT_N_POINTS;
	float x,y, angle = 0;
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(s->color[0], s->color[1], s->color[2]);
	for(i = 0; i<SEGMENT_N_POINTS+2; i++){
		x = SEGMENT_RADIUS*cos(angle);
		y = SEGMENT_RADIUS*sin(angle);

		glNormal3f(-cos(angle), -sin(angle),0.0);
		glVertex3f(x,y,0.0);
		glVertex3f(x,y,-s->length);

		angle += angle_step;
	}
	glEnd();
}

//pysics and so
void segment_refresh(segment_t*, float dt);
