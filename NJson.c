/**
 * @brief Archivo NJson.c con la implementación de primitivas y declaracion de los TDA del Trabajo Práctico Final 
 * 
 * @file NJson.c
 * @author Argueyo Oscar, Diaz Alan
 * @date 2018-06-29
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NJson.h"

/**
 * @brief Primitiva de inicializacion de la estructura njson
 * 
 * @param this 
 * @param nombre
 * @param nombreDato 
 * @param valor 
 * @param sizeDato 
 * @param Array 
 * @param func 
 * @return NJson* 
 */
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

/**
 * @brief Liberacion de la memoria alocada por el njson pasado como parámetro
 * 
 * @param this Puntero a el njson a liberar
 */
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
/**
 * @brief Liberacion de la memoria alocada para un TDA Dato que componen al njson
 * 
 * @param this Puntero al dato que compone al njson
 */
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

/**
 * @brief Primitiva que permite agregar un TDA Dato a la estructura del njson
 * 
 * @param this 
 * @param nombre 
 * @param valor 
 * @param sizeDato 
 * @param Array 
 * @param func funcion de impresion del dato
 */
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

/**
 * @brief Primitiva de agregacion de datos al njson si ya tiene datos, se agrega de manera consecutiva al ultimo dato ingresado
 * 
 * @param dato 
 * @param nombre 
 * @param valor 
 * @param sizeDato 
 * @param Array 
 * @param func 
 * @return Dato* 
 */
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

/**
 * @brief Primitiva de impresion del njson. 
 * Imprime en consola el njson pasado como parametro si el parametro opcion es 0, sino lo imprime sobre el archivo pasado como parametro
 * 
 * @param this 
 * @param out 
 * @param opcion 
 */
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

/**
 * @brief Primitiva de impresión de un tipo de dato entero (con signo) en formato válido Json
 * 
 * @param valor 
 * @param out 
 * @param opcion 
 */
void njson_imprimir_entero(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%d",*(int*)valor);
	}else{
		fprintf(out, "%d",*(int*)valor);
	}

}

/**
 * @brief Primitiva de impresión de un tipo de dato entero (sin signo) en formato válido Json
 * 
 * @param valor 
 * @param out 
 * @param opcion 
 */
void njson_imprimir_unsigned(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%u",*(unsigned*)valor);
	}else{
		fprintf(out, "%u",*(unsigned*)valor);
	}

}

/**
 * @brief Primitiva de impresión de un tipo de dato double en formato válido Json
 * 
 * @param valor 
 * @param out 
 * @param opcion 
 */
void njson_imprimir_double(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%lf",*(double*)valor);
	}else{
		fprintf(out, "%lf",*(double*)valor);
	}
}

/**
 * @brief Primitiva de impresión de un tipo de dato entero float en formato válido Json 
 * 
 * @param valor 
 * @param out 
 * @param opcion 
 */
void njson_imprimir_float(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("%f",*(float*)valor);
	}else{
		fprintf(out, "%f",*(float*)valor);
	}
}

/**
 * @brief Primitiva de impresión de un tipo de dato string en formato válido Json
 * 
 * @param valor 
 * @param out 
 * @param opcion 
 */
void njson_imprimir_string(void* valor, FILE* out, unsigned opcion){
	if(opcion == 0){
		printf("\"%s\"",(char*)valor);
	}else{
		fprintf(out, "\"%s\"",(char*)valor);
	}

}

/**
 * @brief Primitiva de impresión de un tipo de dato Boolean en formato válido Json: true o false
 * 
 * @param valor 
 * @param out 
 * @param opcion 
 */
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

/**
 * @brief Primitiva del TDA njson de impresion del contenido del njson en un archivo con nombre filename
 * 
 * @param this 
 * @param filename 
 * @return unsigned int Retorna 1 si se pudo escribir en el archivo, o 0 si no se pudo.
 */
unsigned int njson_tofile(NJson* this , char* filename){

	FILE* out;

	if((out = fopen((char*)filename,"w")) != NULL){
		njson_print(this,out,1);
	}

	if	(fclose(out) == EOF){
		return 0;
	}
	return 1;

}


/**
 * @brief Primitiva del TDA njson para obtener el dato a partir de una clave dada, se guarda el dato en la variable dato_encontrado
 * 
 * @param this 
 * @param clave 
 * @param dato_encontrado 
 * @return int 1 si encontro el dato, o 0 si la clave no se encontro en el json.
 */
int njson_obtener_dato(NJson* this, char* clave , Dato** dato_encontrado){

	Dato* dato = this->dato;
	int encontrado = 0;
	while(!encontrado && (dato)){
		if(!strcmp(dato->nombre, clave)){
			encontrado = 1;
			*dato_encontrado = dato;
		}else{
			dato = dato->sig;
		}
	}
	return encontrado;
}

/**
 * @brief Primitiva del TDA njson para cambiar el contenido (valor) de un elemento del nsjon, a partir de una clave dada valida
 * 
 * @param this 
 * @param nombre 
 * @param valor 
 * @param sizeDato 
 * @param Array 
 * @param func 
 */
void njson_cambiar_contenido(
    NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
){

    Dato* dato_cambiar;
	
    if(njson_obtener_dato(this, nombre, &dato_cambiar)){
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

/**
 * @brief Primitiva del nsjon para imprimir los datos que lo componen, se invoca la funcion de impresion de cada dato o si es un array de datos 
 * se itera sobre estos aplicando la funcion de impresion para cada elemento del arreglo.
 * 
 * @param dato 
 * @param out 
 * @param opcion 
 */
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
/**
 * @brief Primitiva del nsjon para la impresion de coleccion de un mismo tipo de dato
 * 
 * @param dato 
 * @param out 
 * @param opcion 
 */
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
