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
	char* data = '{"size":"0 bytes","hash":"37eb1ba1849d4b0fb0b28caf7ef3af52","bytes":0,"thumb_exists":false,"rev":"714f029684fe","modified":"Wed, 27 Apr 2011 22:18:51 +0000","path":"/Photos","is_dir":true,"icon":"folder","root":"dropbox","contents":[{"size":"2.3 MB","rev":"38af1b183490","thumb_exists":true,"bytes":2453963,"modified":"Mon, 07 Apr 2014 23:13:16 +0000","client_mtime":"Thu, 29 Aug 2013 01:12:02 +0000","path":"/Photos/flower.jpg","photo_info":{"lat_long":[37.77256666666666,-122.45934166666667],"time_taken":"Wed, 28 Aug 2013 18:12:02 +0000"},"is_dir":false,"icon":"page_white_picture","root":"dropbox","mime_type":"image/jpeg","revision":14511}],"revision":29007}';
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
	if	(fclose(out) == EOF){
		return 0;
	}

	return 1;

}

void njson_agregar(NJson* njson, const char* clave, void* value){

}

int njson_existe_clave(NJson* njson, const char* clave){

	return 0;
}

Valor* njson_obtener_clave(NJson* njson, const char* clave){
	Valor* valor;
	return valor;
}

void njson_eliminar_clave(NJson* njson, const char* clave){

}

void njson_liberar(NJson* njson){

}
