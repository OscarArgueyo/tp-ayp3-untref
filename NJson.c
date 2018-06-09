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
	void* (*func)(void*,FILE*,unsigned)
)
{
	this->nombre = malloc(strlen(nombre)+1);
	strcpy(this->nombre,nombre);
	this->dato = malloc(sizeof(Dato));
	this->dato = 0x0;
	this->dato = njson_agregar_siguiente_dato(this->dato,nombreDato,valor,sizeDato,longArray,func);
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
	void* (*func)(void*,FILE*,unsigned)
){
    Dato* dato = this->dato;
	njson_agregar_siguiente_dato(dato,nombre,valor,sizeDato,longArray,func);

	//return dato;

}

Dato* njson_agregar_siguiente_dato(
	Dato* dato, 
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
){
	if(!dato){
			//puts("estamos aca");
			//exit(1);
			dato = malloc(sizeof(Dato));
			dato->nombre = malloc(strlen(nombre)+1);
			strcpy(dato->nombre,nombre);
			dato->valor = malloc(sizeDato);
			memcpy(dato->valor,valor,sizeDato);
			dato->longArray = longArray;
			dato->sizeDato = sizeDato;
			dato->func = func;
			dato->sig = 0x0;

	}else{
		dato->sig = njson_agregar_siguiente_dato(dato->sig,nombre,valor,sizeDato,longArray,func);
	}

	return dato;


}

void njson_print(NJson* this, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("{\n");
		Dato* datoEscribir = this->dato;
		while(datoEscribir){
			njson_dato_escribir(datoEscribir, NULL, 0);
			datoEscribir = datoEscribir->sig;
			if(datoEscribir != 0x0){
				printf(",\n");
			}
		}
		printf("\n}");
	}else{
		fprintf(out, "{\n");
		Dato* datoEscribir = this->dato;
		while(datoEscribir){
			njson_dato_escribir(datoEscribir,out,1);
			datoEscribir = datoEscribir->sig;
			if(datoEscribir != 0x0){
				fprintf(out, ",\n");
			}
		}
		fprintf(out, "\n}");
	}
}

void njson_imprimir_entero(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%d",*(int*)valor);
	}else{
		fprintf(out, "%d",*(int*)valor);
	}

}

void njson_imprimir_unsigned(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%u",*(unsigned*)valor);
	}else{
		fprintf(out, "%u",*(unsigned*)valor);
	}

}

void njson_imprimir_double(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%lf",*(double*)valor);
	}else{
		fprintf(out, "%lf",*(double*)valor);
	}
}

void njson_imprimir_float(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%f",*(float*)valor);
	}else{
		fprintf(out, "%f",*(float*)valor);
	}
}

void njson_imprimir_string(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("\"%s\"",(char*)valor);
	}else{
		fprintf(out, "\"%s\"",(char*)valor);
	}

}

void njson_imprimir_boolean(void* valor, FILE* out, unsigned opcion){
	char bool = *(char*)valor;
	if(opcion == 0){
		if(bool == '0'){
			printf("false");
		}else{
			printf("true");
		}
	}else{
		if(bool == '0'){
			fprintf(out, "false");
		}else{
			fprintf(out, "true");
		}
	}

}

unsigned int njson_tofile(NJson* this , char* filename){

	FILE* out;

	if((out = fopen((char*)filename,"w")) != NULL){
		njson_print(this,out,1);
	}

	fclose(out);

	/*
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
	*/
	return 1;

}

/**
Primitivas de la entrega 3
*/


Dato* njson_obtener_dato(NJson* this, char* clave , Dato* dato_encontrado){

	Dato* dato = this->dato;
	int encontrado = 0;
	while(!encontrado && (dato)){
		if(!strcmp(dato->nombre, clave)){
			encontrado = 1;
			//dato_encontrado = dato;
		}else{
			dato = dato->sig;
		}
	}
	//return encontrado;
	return dato;
}

void njson_cambiar_contenido(
    NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
){
	Dato* dato_cambiar = 0x0;
    dato_cambiar = njson_obtener_dato(this, nombre, dato_cambiar);
	//Dato* dato_cambiar;
    //if(njson_obtener_dato(this, nombre, dato_cambiar)){
	if(dato_cambiar){
		dato_cambiar->valor = realloc(dato_cambiar->valor,sizeDato);
		memcpy(dato_cambiar->valor,valor,sizeDato);
		dato_cambiar->sizeDato = sizeDato;
		dato_cambiar->longArray = longArray;
		dato_cambiar->func = func;
        puts("Se cambio el dato");
    }else{
        puts("No se cambio el dato, porque no se encontro");
    }

}

void njson_dato_escribir(Dato* dato, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("\t\"");
		printf("%s",dato->nombre);
		printf("\": ");
		if(dato->longArray > 0){
			njson_imprimir_array(dato,NULL,0);
		}else{
			dato->func(dato->valor,NULL,0);
		}
	}else{
		fprintf(out,"\t\"");
		fprintf(out, "%s",dato->nombre);
		fprintf(out,"\": ");
		if(dato->longArray > 0){
			njson_imprimir_array(dato,out,opcion);
		}else{
			dato->func(dato->valor, out, 1);
		}
	}

}

void njson_imprimir_array(Dato* dato, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("[");
		for(int i = 0; i < dato->longArray; i++){
			dato->func(dato->valor+(i*(dato->sizeDato)/dato->longArray),NULL,0);
			if(i+1 != dato->longArray){
				printf(",");
			}
		}
		printf("]");
	}else{
		fprintf(out, "[");
		for(int i = 0; i < dato->longArray; i++){
			dato->func(dato->valor+(i*(dato->sizeDato)/dato->longArray),out,1);
			if(i+1 != dato->longArray){
				fprintf(out, ",");
			}
		}
		fprintf(out, "]");
	}
}
