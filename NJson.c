
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NJson.h"

NJson* njson_init(NJson* this, char* nombre, char* nombreDato, void* valor,
		unsigned sizeDato, char array, unsigned longArray, void* (*func)(char*,void*)){
	this->nombre = malloc(strlen(nombre)+1);
	strcpy(this->nombre,nombre);
	this->dato = malloc(sizeof(Dato));
	this->dato = 0x0;
	this->dato = agregarDato(this->dato,nombreDato,valor,sizeDato,array,longArray,func);
	return this;

}

void njson_release(NJson* this){
	if(this){
		free(this->nombre);
		this->nombre = 0x0;
		dato_release(this->dato);
		this->dato = 0x0;
		free(this);
	}

}

void dato_release(Dato* this){
	if(this){
		free(this->nombre);
		this->nombre = 0x0;
		free(this->valor);
		this->valor = 0x0;
		free(this);
		dato_release(this->sig);
	}
}

Dato* agregarDato(Dato* this, char* nombre, void* valor, unsigned sizeDato, char array,
		unsigned longArray, void* (*func)(char*,void*)){

	if(!this){
		this = malloc(sizeof(Dato));
		this->nombre = malloc(strlen(nombre)+1);
		strcpy(this->nombre,nombre);
		this->valor = malloc(sizeDato);
		memcpy(this->valor,valor,sizeDato);
		this->longArray = longArray;
		this->array = array;
		this->func = func;
		this->sig = 0x0;
	}else{
		this->sig = agregarDato(this->sig,nombre,valor,sizeDato,array,longArray,func);
	}
	return this;

}

char* escribir(char* string, NJson* this){

	//string = malloc(2);
	//strcat(string,"{\n");
	printf("{\n");
	Dato* datoEscribir = this->dato;
	while(datoEscribir){
		//string = realloc(string, strlen(string)+strlen(datoEscribir->nombre)+4);
		//strcat(string,"\"");
		//strcat(string,datoEscribir->nombre);
		//strcat(string,"\":");
		printf("\"");
		printf("%s",datoEscribir->nombre);
		printf("\": ");
		datoEscribir->func(string,datoEscribir->valor);
		datoEscribir = datoEscribir->sig;
	}
	//string = realloc(string,strlen(string)+2);
	//strcat(string,"}\n");

	printf("}\n");

	return string;

}

void escribirEntero(char* string, void* valor){
	//string = realloc(string,strlen(string)+10);
	//sprintf(string,"%s %d",string,*(int*)valor);
	//strcat(string,",\n");
	printf("%d",*(int*)valor);
	printf(",\n");
}

void escribirUnsigned(char* string, void* valor){
	//string = realloc(string,strlen(string)+10);
	//sprintf(string,"%s %u",string,*(unsigned*)valor);
	//strcat(string,",\n");
	printf("%u",*(unsigned*)valor);
	printf(",\n");
}

void escribirDouble(char* string, void* valor){
	//string = realloc(string,strlen(string)+10);
	//sprintf(string,"%s %lf",string,*(double*)valor);
	//strcat(string,",\n");
	printf("%lf",*(double*)valor);
	printf(",\n");
}

void escribirFloat(char* string, void* valor){
	//string = realloc(string,strlen(string)+10);
	//sprintf(string,"%s %f",string,*(float*)valor);
	//strcat(string,",\n");
	printf("%f",*(float*)valor);
	printf(",\n");
}

void escribirString(char* string, void* valor){
	//char* texto = (char*)valor;
	//string = realloc(string,strlen(string)+strlen(texto)+3);
	//sprintf(string,"%s \"%s\"",string,texto);
	//strcat(string,",\n");
	printf("\"%s\"",(char*)valor);
	printf(",\n");
}

void escribirBoolean(char* string, void* valor){
	char bool = *(char*)valor;
	//string = realloc(string,strlen(string)+6);
	if(bool == '0'){
		//sprintf(string,"%s false",string);
		printf("false");
	}else{
		//sprintf(string,"%s true",string);
		printf("true");
	}
	//strcat(string,",\n");
	printf(",\n");
}

unsigned int njson_tofile(NJson* this , char* filename){

	FILE *out;

	if((out=freopen((char*)filename, "w" ,stdout))==NULL) {
	    printf("No pudo abrirse correctamente el archivo.\n");
    	exit(1);
    	return 0;
  	}

	escribir(0x0, this);

	if	(fclose(out) == EOF){
		return 0;
	}

	return 1;

}


/*
NJson* njson_init(NJson* this){
	return this;
}

char* njson_tostring(NJson* this){

	char* data ="{\"size\":\"0 bytes\",\"hash\":\"37eb1ba1849d4b0fb0b28caf7ef3af52\",\"bytes\":0,\"thumb_exists\":false,\"rev\":\"714f029684fe\",\"modified\":\"Wed, 27 Apr 2011 22:18:51 +0000\",\"path\":\"/Photos\",\"is_dir\":true,\"icon\":\"folder\",\"root\":\"dropbox\",\"contents\":[{\"size\":\"2.3 MB\",\"rev\":\"38af1b183490\",\"thumb_exists\":true,\"bytes\":2453963,\"modified\":\"Mon, 07 Apr 2014 23:13:16 +0000\",\"client_mtime\":\"Thu, 29 Aug 2013 01:12:02 +0000\",\"path\":\"/Photos/flower.jpg\",\"photo_info\":{\"lat_long\":[37.77256666666666,-122.45934166666667],\"time_taken\":\"Wed, 28 Aug 2013 18:12:02 +0000\"},\"is_dir\":false,\"icon\":\"page_white_picture\",\"root\":\"dropbox\",\"mime_type\":\"image/jpeg\",\"revision\":14511}],\"revision\":29007}";
	return data;
}

void njson_print(NJson* this){

	puts(njson_tostring(this));

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
*/
