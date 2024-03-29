#include "renderer_t.h"

//initalizes renderer
int renderer_init(renderer_t* r){
	r->screen = NULL;
	r->screenshot_file_name = NULL;


	//load and compile shaders
	//read shader text
	glewInit();
	FILE * shadersourcef = fopen("shaders/green.fr","r");
	char src[1000];
	char * p = src;
	if(shadersourcef != NULL){
		while((*(p++) = fgetc(shadersourcef))!= EOF );
		*--p = 0;
		p = src;
		fclose(shadersourcef);
		printf("kupa\n");
		int param;

		//create shader

		uint32_t green_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(green_shader, 1, (const char **)&p, NULL);
		glCompileShader(green_shader);

		glGetShaderiv(green_shader, GL_COMPILE_STATUS, &param);
		if(param == GL_TRUE){
			printf("green shader successfully compiled\n");
		}
		r->green_program = glCreateProgram();
		glAttachShader(r->green_program, green_shader);
		glLinkProgram(r->green_program);
		//glUseProgram(r->green_program);
	}
	return 0 ;
}

//deletes renderer
void renderer_delete(renderer_t* r){
	//we delete screenshot filename
	free(r->screenshot_file_name);
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
	//enable texturing

	//set proper winding
	glFrontFace(r->winding);

	//set shade mode#include <displayable_object_t.h>l
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
	//clear context
	glClearColor(0.0,0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//reset matrix state
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//apply camera transform
	body_apply_inverted_transform(r->camera);
}


//finishes rendering
void renderer_finish(renderer_t* r){
	glFlush();

	//if screenshot was requested, make it
	if(r->screenshot_file_name != NULL){
		SDL_Surface *screenshot = SDL_CreateRGBSurface(SDL_HWSURFACE, r->window_width,
				r->window_height, 24, 0xff0000, 0x00ff00, 0x0000ff, 0x000000);

		glReadPixels(0,0,r->window_width, r->window_height, GL_BGR, GL_UNSIGNED_BYTE, screenshot->pixels);
		SDL_SaveBMP(screenshot, r->screenshot_file_name);
		SDL_FreeSurface(screenshot);
		free(r->screenshot_file_name);
		r->screenshot_file_name = NULL;
	}

	//display everything on screen
	SDL_GL_SwapBuffers();
}

//sets renderer camera(point of view)
void renderer_set_camera(renderer_t* r, body_t* camera){
	r->camera = camera;
}

//saves screenshot to a file of given name
void renderer_screenshot(renderer_t* r, const char *filename){
	r->screenshot_file_name = (char*)malloc(strlen(filename) + 1);
	strcpy(r->screenshot_file_name, filename);
}
