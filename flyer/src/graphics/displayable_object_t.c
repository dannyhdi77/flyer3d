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
	d->x_angle = 0.0;
	d->y_angle = 0.0;
	vector3_set(d->position, 0.0, 0.0, 0.0);
	vector3_set(d->forward, 0.0, 0.0, 1.0);
	vector3_set(d->up, 0.0, 1.0, 0.0);
}

//apply object transform
void d_object_apply_transform(displayable_object_t* obj, void* r){
	vector3_t x_axis;
	vector3_cross_product(x_axis, obj->up, obj->forward);
	float transform_matrix[16] = {x_axis[0],x_axis[1],x_axis[2], 0,
			0,1,0,0,
			0,0,1,0,
			obj->position[0],obj->position[1],obj->position[2],1};
	glMultMatrixf(transform_matrix);
}

//draw object
void d_object_display(displayable_object_t* obj, void* r){
	if(obj->type == DISP_MODEL){
		model_display(obj->data);
	}
}
