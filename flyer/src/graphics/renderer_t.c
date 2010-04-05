#include "renderer_t.h"

//initalizes renderer
int renderer_init(renderer_t* r){
	r->screen = NULL;
	list_init(&(r->rendering_queue), sizeof(body_t*), NULL);
	return 0 ;
}

//deletes renderer
void renderer_delete(renderer_t* r){
	//we delete only dynamic data structure
	list_delete(&r->rendering_queue);
}

void renderer_reload(renderer_t* r){
	//delete old screen
	if(r->screen != NULL)
		SDL_FreeSurface(r->screen);

	//create new
	r->screen = SDL_SetVideoMode(r->window_width, r->window_height, r->window_bpp, r->video_mode_flags);

	//calculate new clip volume dimensions
	renderer_resize(r,r->window_width,r->window_height);

	//set viewport to current window dimensions
	glViewport(0,0,r->window_width,r->window_height);

	//reset coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//create clipping volume
	float w = r->clip_width/2;
	float h = r->clip_height/2;
	float d = r->clip_depth/2;


	if(r->projection == REND_ORTHO)
		glOrtho(-w, w, -h, h, d, -d);	//orthographic projection
	else
		gluPerspective(r->view_angle, w/h, r->near, r->far);

	//opengl flags
	if((r->renderer_flags & REND_DEPTH_TEST) == REND_DEPTH_TEST){
		glEnable(GL_DEPTH_TEST);
	}

	if((r->renderer_flags & REND_CULLING) == REND_CULLING){
		glEnable(GL_CULL_FACE);
	}

	if((r->renderer_flags & REND_LIGHTS) == REND_LIGHTS){
		glEnable(GL_LIGHTING);
		//set ambient light
		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,r->ambient_color);
		//also enables color following
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	}

	//set proper winding
	glFrontFace(r->winding);

	//set shade model
	glShadeModel(r->shade_model);
}

//fuction for resize event, simply recalculates clipping volume
void renderer_resize(renderer_t* r, int w, int h){
	if(h == 0)
		h = 1;

	r->window_height = h;
	r->window_width = w;

	if(w > h){
		r->clip_width = r->base_clip_size*w/h;
		r->clip_height = r->base_clip_size;
	}
	else{
		r->clip_width = r->base_clip_size;
		r->clip_height = r->base_clip_size/(w/h);
	}
}

//starts rendering mode
void renderer_start(renderer_t* r){
	//delete old list, create new
	list_delete(&r->rendering_queue);
	list_init(&r->rendering_queue,sizeof(body_t*),NULL);
	//save matrix state
	glPushMatrix();
}

void renderer_draw_object(void * vobj){
	body_t *obj = *(body_t**)vobj;
	glPushMatrix();	//save matrix state
		body_apply_transform(obj);
		d_object_display(&obj->model);
	glPopMatrix();
}

//finishes rendering
void renderer_finish(renderer_t* r){
	//actual rendering
	glClearColor(0.1,0.1, 0.1, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//draw everything from the queue
	list_iterate(&r->rendering_queue, &renderer_draw_object, NULL);

	glFlush();
	SDL_GL_SwapBuffers();

	//restore matrix state
	glPopMatrix();
}

//adds object to rendering queue
void renderer_display(renderer_t* r, body_t* obj){
	list_insert(&r->rendering_queue, &obj);
}
