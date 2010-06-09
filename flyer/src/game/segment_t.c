/*
 * segment_t.c
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#include <segment_t.h>

//sets some basic properties
void segment_init(segment_t* s, float length){
	s->type = SEGMENT_NORMAL;
	body_init(&s->obj);
	s->length = length;
	vector3_set(s->color, 1.0, 0.0, 0.0);	//default color
}

//initalizes segment as connector beetween two normal segments
void segment_init_connector(segment_t* s, segment_t* prev, segment_t* next, float upr, float outr){
	s->type = SEGMENT_CONNECTOR;
	s->length = SEGMENT_GAP;
	body_init(&s->obj);
	//copy colors
	vector3_set_v(s->color, prev->color);
	vector3_set_v(s->next_color, next->color);
	//set rotations
	s->out_rotation = outr;
	s->up_rotation = upr;
	//find location
	s->obj = prev->obj;
	body_move_forward(&s->obj, -prev->length);
}


//deletes segment
void segment_delete(segment_t* s){
	//do nothing
}

//prints segment
void segment_display(segment_t* s, void* nul){
	glPushMatrix();
	body_apply_transform(&s->obj);
	int i;
	float angle_step = 2*3.1415/SEGMENT_N_POINTS;
	float x,y, angle = 0;
	if(s->type == SEGMENT_NORMAL){
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
	else{
		glBegin(GL_TRIANGLE_STRIP);
		vector3_t p,term, vx,vy, normal;
		//we obtain new axes
		vector3_set(vx, 1.0, 0.0, 0.0);
		vector3_set(vy, 0.0, 1.0, 0.0);
		vector3_rotate(vx,vy,s->up_rotation);
		vector3_rotate(vy,vx,s->out_rotation);

		for(i = 0; i<SEGMENT_N_POINTS+2; i++){
			x = SEGMENT_RADIUS*cos(angle);
			y = SEGMENT_RADIUS*sin(angle);
			glColor3f(s->color[0], s->color[1], s->color[2]);
			glNormal3f(-cos(angle), -sin(angle),0.0);
			glVertex3f(x,y,0.0);

			glColor3f(s->next_color[0], s->next_color[1], s->next_color[2]);
			vector3_set(p,0.0,0.0,-SEGMENT_GAP);
			vector3_set(normal, 0.0,0.0,0.0);

			vector3_set_v(term, vx);
			vector3_scale(term, x);
			vector3_add(p, term);
			vector3_add(normal, term);

			vector3_set_v(term, vy);
			vector3_scale(term, y);
			vector3_add(p, term);
			vector3_add(normal, term);
			vector3_normalize(normal);
			glNormal3f(-normal[0], -normal[1], -normal[2]);
			glVertex3f(p[0], p[1], p[2]);

			angle += angle_step;
		}
		glEnd();
	}
	glPopMatrix();
}

//pysics and so
void segment_refresh(segment_t*, float dt);

//returns 1 if point is inside segment
int segment_in(segment_t* s, vector3_t v){
	vector3_t tp; //transformed position
	vector3_set_v(tp,v);
	body_transform_vector(&s->obj, tp);
	if(-tp[2] > s->length + SEGMENT_HOLD)
		return 0;
	else
		return 1;
}


void segment_collide(segment_t *s, struct collision_s* c){
	vector3_t tp; //transformed position
	vector3_set_v(tp,c->point);
	body_transform_vector(&s->obj, tp);
	//vector3_print(tp);

	int result = 0;
	//first of all, we check z coordinate
	if((-tp[2] > 0)&&(-tp[2] < s->length)){
		if(sqrt(tp[0]*tp[0] + tp[1]*tp[1]) > SEGMENT_RADIUS){
			result = 1;
		}
		else{
			result = 0;
		}
	}
	else{
		result =  0;
	}
	c->collides |= result;
}
