/*
 * nJson.c
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NJson.h";


char * njson_tostring(NJson* this){
	/**
	 * Para esta entrega 1 lo vamos a hacer aca
	 * Este sera el metodo mas complicado de todos.
	 *
	 */
	char* data = 'ACA VA EL JSON';
	return data;
}

void njson_print(NJson* this){

	puts(njson_tostring(this));

}

unsigned int njson_tofile(NJson* this , char* filename){

	FILE *out;
	char* data = njson_tostring(this);
	out = fopen( filename, "w");
	fputs(data , out);
	fclose(out);

}

void njson_agregar(NJson* njson, const char* clave, void* value){

}

int njson_existe_clave(NJson* njson, const char* clave){

}

Valor* njson_obtener_clave(NJson* njson, const char* clave){

}

void njson_eliminar_clave(NJson* njson, const char* clave){

}

void njson_liberar(NJson* njson){

}
