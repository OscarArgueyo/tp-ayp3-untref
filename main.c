#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NJson.h"

#define NAME_MAX 255 // Largo máximo para nombre de archivos en linux.
int main(int argc, char* argv[]) {

	NJson njson;
	char* escritura = 0x0;

	unsigned valor1 = 55;
	int valor2 = 8;
	double valor3 = 11.27;
	float valor4 = 15.12;
	char valor5 = 1;
	char* valor6 = "714f129684fe";

	njson_init(&njson,"PruebaJson","numero1",&valor1,sizeof(unsigned),0,1,escribirUnsigned);
	agregarDato(njson.dato,"numero2",&valor2,sizeof(int),0,1,escribirEntero);
	//agregarDato(njson.dato,"numero3",&valor3,sizeof(double),0,1,escribirDouble);
	//agregarDato(njson.dato,"numero4",&valor4,sizeof(float),0,1,escribirFloat);
	agregarDato(njson.dato,"boolean",&valor5,sizeof(char),0,1,escribirBoolean);
	//agregarDato(njson.dato,"texto",valor6,strlen(valor6),0,1,escribirString);

	escritura = escribir(escritura,&njson);

	printf("%s",escritura);

	//njson_release(&njson);
	/*
	char* nombre_archivo[NAME_MAX];

	if	(argc == 3 || argc == 1){//Podemos avanzar

		if(argc == 1){ //No tenemos parametros
			njson_print(pnjson);
		}


		if(argc == 3){ //Tenemos dos parametros -f y nombre archivo

			if (strcmp(argv[1], "-f") == 0 && strlen(argv[2]) <= NAME_MAX){
				*nombre_archivo = argv[2];
				njson_tofile(pnjson , *nombre_archivo);

			}//Validar -f

			//Validar nombre archivo y guardarlo en nombre_archivo

		}

	}else{
		exit(0);
	}*/

}

