/*
 * renderer_t.h
 *
 *  Created on: 2010-04-01
 *      Author: krzychu
 *
 *      General graphics system
 */


#ifndef RENDERER_T_H_
#define RENDERER_T_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include <list_t.h>
#include <body_t.h>
#include <displayable_object_t.h>
#include <light_t.h>

//renderer flags
//type of projection
#define	REND_ORTHO 0
#define REND_PERSPECTIVE 2
//type of resulting image
#define	REND_NORMAL	0
#define REND_ANAGLYPH 2
//culling
#define REND_CULLING 0X0001
//depth testing
#define REND_DEPTH_TEST	0X0002
//light
#define REND_LIGHTS 0X0004

//all data needed to render image on screen
typedef struct{
	SDL_Surface *screen;	//current sdl screen

	//orthographic projection
	float clip_height;	//height of clipping volume
	float clip_width;	//width of clipping volume
	float base_clip_size;	//guarantees that min(width, height) = base
	float clip_depth;	//depth of clipping volume
	//perspective projection
	float view_angle;
	float near, far;

	int window_width;	//guess what it is
	int window_height;	//yo feel the flow
	int window_bpp;	//color depth of window

	//flags, flags, flags
	unsigned int video_mode_flags;	//sdl flags
	unsigned int opengl_flags; //flags for glEnable
	unsigned int renderer_flags; //flags for renderer itself
	unsigned int winding;	//clockwise or counterclockwise winding

	//settings
	char projection;	//type of projection
	char image_type;	//type of image
	unsigned int shade_model;	//gl shade model

	//light settings
	color_t ambient_color;	//ambient light color

	//list of objects to render
	list_t rendering_queue;

} renderer_t;

//initalizes renderer structure
int renderer_init(renderer_t*);

//destroy renderer
void renderer_delete(renderer_t*);

//function handling resize event
//arguments: renderer, width, height
void renderer_resize(renderer_t*, int, int);

//function applying changes in renderer structure to display
void renderer_reload(renderer_t*);

//starts rendering mode
void renderer_start(renderer_t*);

//finishes rendering
void renderer_finish(renderer_t*);

//adds object to rendering queue
void renderer_display(renderer_t*, body_t*);

#endif /* RENDERER_T_H_ */
