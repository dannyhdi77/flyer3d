/*
 * main_menu_create.c
 *
 *  Created on: 2010-05-17
 *      Author: krzychu
 */
#include <main_menu_create.h>

void main_menu_create(menu_t* m){
	m->n_items = 2;
	m->items = (menu_item_t*)malloc(sizeof(menu_item_t)*m->n_items);

	m->items[0].parent = m;
	strcpy( m->items[0].image_file_name, "data/menu/nowa_gra.bmp");

	m->items[1].parent = m;
	strcpy( m->items[1].image_file_name, "data/menu/nowa_gra.bmp");
}
