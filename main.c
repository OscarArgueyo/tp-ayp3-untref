#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NJson.h"

#define NAME_MAX 255 // Largo máximo para nombre de archivos en linux.
void main(int argc, char* argv[]) {

	NJson njson;
	char* escritura = 0x0;

	/**
	 * Declaracion del puntero al nombre del archivo si lo necesitamos segun
	 * opciones de ejecucion
	*/
	char* nombre_archivo[NAME_MAX];

	/**
	 * Declaracion de variables a guardarse en el json para probar el funcionamiento
	 *
	*/
	unsigned valorUnsigned = 55;
	int valorInteger = 8;
	double valorDouble = 11.28;
	float valorFlotante = 15.12;
	char valorBoleano = 1;
	char* valorString = "714f129684fe";

	/*
	*   Hacer 2 func de datoAgregar, una con el json y otra con el dato sig
	*/

	njson_init(&njson,"PruebaJson","numero1 unsigned",&valorUnsigned,sizeof(unsigned),0,(void*)&njson_imprimir_unsigned);
	njson_dato_agregar(&njson,"numero2 integer",&valorInteger,sizeof(int),0,(void*)&njson_imprimir_entero);
	njson_dato_agregar(&njson,"numero3 double",&valorDouble,sizeof(double),0,(void*)&njson_imprimir_double);
	njson_dato_agregar(&njson,"numero4 float",&valorFlotante,sizeof(float),0,(void*)&njson_imprimir_float);
	njson_dato_agregar(&njson,"boolean",&valorBoleano,sizeof(char),0,(void*)&njson_imprimir_boolean);
	njson_dato_agregar(&njson,"texto",valorString,strlen(valorString)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"numero3 otra vez",&valorDouble,sizeof(double),0,(void*)&njson_imprimir_double);
	/*njson_dato_agregar(&njson,"boolean otra vez",&valorBoleano,sizeof(char),0,(void*)&njson_imprimir_boolean);
	njson_dato_agregar(&njson,"numero4 otra vez",&valorFlotante,sizeof(float),0,(void*)&njson_imprimir_float);
	*/

	if	(argc == 3 || argc == 1){
		//Podemos avanzar
		if(argc == 1){ //No tenemos parametros OK
			//njson_print(pnjson);
			njson_print(&njson);
		}

		if(argc == 3){ //Tenemos dos parametros -f y nombre archivo

			//Valido las opciones pasadas. OK
			//Validar -f OK
			//Validar nombre archivo y guardarlo en nombre_archivo OK
			if (strcmp(argv[1], "-f") == 0 && strlen(argv[2]) <= NAME_MAX){

				*nombre_archivo = argv[2];

				//Guardo en njson en un archivo con nombre "nombre_archivo".
				njson_tofile(&njson , *nombre_archivo);

			}
		}


	}

	//Termino el programa, libero la memoria del njson para evitar goteo de memoria
	njson_release(&njson);


}//Fin main

