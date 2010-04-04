/*
 * default_game_renderer_settings.c
 *	temporary file for renderer inital settings
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */
#include "renderer_t.h"
#include "default_game_renderer_settings.h"

void default_game_renderer_settings(renderer_t *r){
	r->window_height = 600;
	r->window_width = 800;
	r->window_bpp = 8;

	r->base_clip_size = 10.0;
	r->clip_depth = 10.0;

	r->video_mode_flags = SDL_OPENGL | SDL_RESIZABLE;
	r->renderer_flags = REND_DEPTH_TEST | REND_LIGHTS ;
	r->winding = GL_CCW;

	r->projection = REND_PERSPECTIVE;
	r->far = 400.0;
	r->near = 1.0;
	r->view_angle = 60.0;

	r->shade_model = GL_FLAT;

	r->ambient_color[0] = 1.0;
	r->ambient_color[1] = 1.0;
	r->ambient_color[2] = 1.0;
	r->ambient_color[3] = 1.0;

}
