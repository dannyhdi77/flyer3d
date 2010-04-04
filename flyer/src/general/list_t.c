/*
 * list_t.c
 *
 *  Created on: 2010-03-31
 *      Author: krzychu
 */

#include <list_t.h>

//init list: (list pointer, size of element, destroyer function)
void list_init(list_t* l, size_t s, void_fun_t f){
	l->length = 0;
	l->elem_size = s;
	l->destroyer = f;
	l->head = NULL;
}

//deletes list
void list_delete(list_t* l){
	if(l->destroyer != NULL)
		list_iterate(l,l->destroyer, NULL);

	list_elem_t* tmp;
	while(l->head != NULL){
		tmp = l->head->next;
		free(l->head->data);
		free(l->head);
		l->head = tmp;
	}
}

//inserts element to the front of list
void list_insert(list_t* l, void* elem){
	l->length++;
	//new head
	if(l->head == NULL){
		l->head = (list_elem_t*)malloc(sizeof(list_elem_t));
		l->head->next = NULL;
	}
	else{
		list_elem_t* tail = l->head;
		l->head = (list_elem_t*)malloc(sizeof(list_elem_t));
		l->head->next = tail;
	}

	l->head->data = malloc(l->elem_size);
	memcpy(l->head->data, elem, l->elem_size);
}

//iterates given function through list
void list_iterate(list_t* l, void_fun_t f, void* opt_args){
	list_elem_t* itr;
	for(itr = l->head; itr != NULL ; itr = itr->next){
		(*f)(itr->data, opt_args);
	}
}

//rewrites content of list into specified table in
//reversed order
void list_to_table(list_t* l, void* table){
	list_elem_t* itr;
	int i = 1;
	for(itr = l->head; itr != NULL ; itr = itr->next, i++){
		memcpy(((char*)table) + (l->length - i)*l->elem_size,itr->data, l->elem_size);
	}
}
