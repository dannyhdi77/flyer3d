/*
 * load_texture.c
 *
 *  Created on: 2010-06-10
 *      Author: krzychu
 */
#include <load_texture.h>


//loads texture for us, and returns its handle
int load_texture(const char* filename){
	SDL_Surface *surface; // Gives us the information to make the texture
	if ( (surface = SDL_LoadBMP(filename)) ) {

		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}

		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}

		// Have OpenGL generate a texture object handle for us
		int texture;
		glGenTextures( 1, &texture );

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );

		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0,  GL_RGB, surface->w, surface->h, 0,
					  GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels );
		SDL_FreeSurface(surface);
		return texture;
	}
	else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		return -1;
	}
}
