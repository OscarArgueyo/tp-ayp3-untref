#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NJson.h"

NJson* njson_init(
	NJson* this, 
	char* nombre, 
	char* nombreDato, 
	void* valor,
	unsigned sizeDato,
	char array, 
	unsigned longArray, 
	void* (*func)(void*)
)
{
	this->nombre = malloc(strlen(nombre)+1);
	strcpy(this->nombre,nombre);
	this->dato = malloc(sizeof(Dato));
	this->dato = 0x0;
	this->dato = dato_agregar(this->dato,nombreDato,valor,sizeDato,array,longArray,func);
	return this;

}

void njson_release(NJson* this){
	if(this){
		free(this->nombre);
		this->nombre = 0x0;
		dato_release(this->dato);
		free(this->dato);
		this->dato = 0x0;
		
		//free(this);
		memset(this , 0x0, sizeof(NJson));
		this = 0x0;
	}

}

void dato_release(Dato* this){
	if(this){
		free(this->nombre);
		this->nombre = 0x0;
		free(this->valor);
		this->valor = 0x0;
		if(this->sig != 0x0){
			dato_release(this->sig);
			free(this->sig);
		}
			
		//Libero todo bien
	}
	
}

Dato* dato_agregar(
	Dato* this, 
	char* nombre, 
	void* valor, 
	unsigned sizeDato, 
	char array,
	unsigned longArray, 
	void* (*func)(void*)
){

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
		this->sig = dato_agregar(this->sig,nombre,valor,sizeDato,array,longArray,func);
	}
	return this;

}

void njson_print(NJson* this){

	printf("{\n");
	Dato* datoEscribir = this->dato;
	while(datoEscribir){
		printf("\"");
		printf("%s",datoEscribir->nombre);
		printf("\": ");
		datoEscribir->func(datoEscribir->valor);
		datoEscribir = datoEscribir->sig;
		if(datoEscribir != 0x0){
			printf(",");
		}
	}
	printf("}\n");
}

void imprimir_entero(void* valor){	
	printf("%d",*(int*)valor);

}

void imprimir_unsigned( void* valor){
	printf("%u",*(unsigned*)valor);
	
}

void imprimir_double(void* valor){
	printf("%lf",*(double*)valor);
	
}

void imprimir_float(void* valor){
	printf("%f",*(float*)valor);
}

void imprimir_string(void* valor){
	printf("\"%s\"",(char*)valor);

}

void imprimir_boolean(void* valor){
	char bool = *(char*)valor;
	if(bool == '0'){
		printf("false");
	}else{
		printf("true");
	}
}

unsigned int njson_tofile(NJson* this , char* filename){

	FILE *out;

	if((out=freopen((char*)filename, "w" ,stdout))==NULL) {
	    printf("No pudo abrirse correctamente el archivo.\n");
    	exit(1);
    	return 0;
  	}
	njson_print(this);
	if	(fclose(out) == EOF){
		return 0;
	}

	return 1;

}
