/*
 * load_texture.h
 *
 *  Created on: 2010-06-10
 *      Author: krzychu
 */

#ifndef LOAD_TEXTURE_H_
#define LOAD_TEXTURE_H_

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

//loads texture for us, and returns its handle
int load_texture(const char* filename);

#endif /* LOAD_TEXTURE_H_ */
