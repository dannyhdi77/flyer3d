/*
 * displayable_object_t.c
 *
 *  Created on: 2010-04-03
 *      Author: krzychu
 */
#include <displayable_object_t.h>

//initalizes object with specified data
void d_object_init(displayable_object_t* d, void* p){
	d->data = p;
}

//draw object
void d_object_display(displayable_object_t* obj){
	if(obj->type == DISP_MODEL){
		model_display(obj->data);
	}
	else if(obj->type == DISP_TERRAIN){
		int i;
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		for(i=0 ; i<1000; i++){
			glVertex3f(-1000.0, -5.0, -i*2.0);
			glVertex3f(1000.0, -5.0, -i*2.0);
		}
		glEnd();

		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		for(i=0 ; i<1000; i++){
			glVertex3f(i*2.0 - 1000, -5.0, 0.0);
			glVertex3f(i*2.0 - 1000, -5.0, -1000.0);
		}
		glEnd();
	}
}
