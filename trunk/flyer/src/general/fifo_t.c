/*
 * fifo_t.c
 *
 *  Created on: 2010-04-14
 *      Author: krzychu
 */

#include <fifo_t.h>


//Initialization
void fifo_init(fifo_t* f, size_t elem_size, int maxsize){
	f->size = 0;
	f->elem_size = elem_size;
	f->max_size  = maxsize;
	f->data = malloc(elem_size*maxsize);
	f->first = f->data;
	f->last = f->data;
}

//destruction
void fifo_delete(fifo_t* f){
	free(f->data);
}

//insert something
int fifo_insert(fifo_t* f, void* e){
	if(f->size == f->max_size)
		return 0;

	f->size++;
	//copy the data
	memcpy(f->first, e,f->elem_size);
	//increment the pointer
	f->first = (char*)f->first + f->elem_size;
	//fix it, if it gets too far
	if(f->first - f->data >= f->elem_size*f->max_size)
		f->first = f->data;

	return 1;
}

//get something
int fifo_get(fifo_t* f, void* e){
	if(f->size == 0)
		return 0;

	f->size--;
	//copy the data
	if(e != NULL)
		memcpy(e, f->last,f->elem_size);
	//increment the pointer
	f->last = (char*)f->last + f->elem_size;
	//fix it, if it gets too far
	if(f->last - f->data >= f->elem_size*f->max_size)
		f->last = f->data;

	return 1;
}

//returns fifo size
int fifo_size(fifo_t* f){
	return f->size;
}

//returns pointer to front of fifo
void* fifo_get_front_pointer(fifo_t* f){
	return f->first;
}

//returns pointer to back of fifo
void* fifo_get_back_pointer(fifo_t* f){
	return f->last;
}
