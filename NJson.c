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
	unsigned longArray,
	void* (*func)(void*)
)
{
	this->nombre = malloc(strlen(nombre)+1);
	strcpy(this->nombre,nombre);
	njson_dato_agregar(this,nombreDato,valor,sizeDato,longArray,func);
	return this;

}

void njson_release(NJson* this){
	if(this){
		free(this->nombre);
		this->nombre = 0x0;
		njson_dato_release(this->dato);
		free(this->dato);
		this->dato = 0x0;

		//free(this);
		memset(this , 0x0, sizeof(NJson));
		this = 0x0;
	}

}

void njson_dato_release(Dato* this){
	if(this){
		free(this->nombre);
		this->nombre = 0x0;
		free(this->valor);
		this->valor = 0x0;
		if(this->sig != 0x0){
			njson_dato_release(this->sig);
			free(this->sig);
		}

		//Libero todo bien
	}

}

void njson_dato_agregar(
	NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*)
){
    Dato* dato = this->dato;
	this->dato = njson_agregar_siguiente_dato(dato,nombre,valor,sizeDato,longArray,func);

	//return dato;

}

Dato* njson_agregar_siguiente_dato(
	Dato* dato, 
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*)
){
	if(!dato){
			dato = malloc(sizeof(Dato));
			dato->nombre = malloc(strlen(nombre)+1);
			strcpy(dato->nombre,nombre);
			dato->valor = malloc(sizeDato);
			memcpy(dato->valor,valor,sizeDato);
			dato->longArray = longArray;
			dato->func = func;
			dato->sig = 0x0;
			
	}else{
		njson_agregar_siguiente_dato(dato->sig,nombre,valor,sizeDato,longArray,func);
	}

	return dato;
}

void njson_print(NJson* this){

	puts("{");
	Dato* datoEscribir = this->dato;
	while(datoEscribir){
		njson_dato_escribir(datoEscribir);
		datoEscribir = datoEscribir->sig;
		if(datoEscribir != 0x0){
			printf(",\n");
		}
	}
	puts("\n}");
}

void njson_imprimir_entero(void* valor){
	printf("%d",*(int*)valor);

}

void njson_imprimir_unsigned(void* valor){
	printf("%u",*(unsigned*)valor);

}

void njson_imprimir_double(void* valor){
	printf("%lf",*(double*)valor);

}

void njson_imprimir_float(void* valor){
	printf("%f",*(float*)valor);
}

void njson_imprimir_string(void* valor){
	printf("\"%s\"",(char*)valor);

}

void njson_imprimir_boolean(void* valor){
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

/**
Primitivas de la entrega 3
*/


int njson_obtener_dato(NJson* this, char* clave , Dato* dato_encontrado){

    Dato* dato = this->dato;
    int encontrado = 0;
	while(!encontrado && (dato)){
            if(!strcmp(dato->nombre ,clave)){
                encontrado = 1;
                dato_encontrado = dato;
            }else{
                dato = dato->sig;
            }
	}
	return encontrado;
}

void njson_cambiar_contenido(
    NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*)
){

    Dato* dato_cambiar;

    if(njson_obtener_dato(this , nombre , dato_cambiar)){
		dato_cambiar->valor = realloc(dato_cambiar->valor,sizeDato);
		memcpy(dato_cambiar->valor,valor,sizeDato);
		dato_cambiar->longArray = longArray;
		dato_cambiar->func = func;
        puts("Se cambio el dato");
    }else{
        puts("No se cambio el dato, porque no se encontro");
    }

}

void njson_dato_escribir(Dato* dato){
        printf("\t\"");
		printf("%s",dato->nombre);
		printf("\": ");
        if(dato->longArray > 0){
            njson_imprimir_array(dato);
        }else{
            dato->func(dato->valor);
        }

}

void njson_imprimir_array(Dato* dato){
    printf("[");
    for(int i = 0; i < dato->longArray; i++){
        dato->func(dato->valor+i);
        if(i+1 != dato->longArray){
            printf(",");
        }
    }
    printf("]");
}
