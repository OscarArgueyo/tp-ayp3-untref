#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NJson.h"

#define NAME_MAX 255 //Largo máximo para nombre de archivos en linux.
int main(int argc, char* argv[]) {
	/*
	NJson* pnjson;
	pnjson = njson_init(pnjson);
	 */
	char* nombre_archivo[NAME_MAX];

	printf("\nPrograma =%s \n", argv[0]);

	if	(argc == 3 || argc == 1){//Podemos avanzar

		if(argc == 1){ //No tenemos parametros
			puts("Aqui estamos\n");
		}


		if(argc == 3){ //Tenemos dos parametros -f y nombre archivo
			//Validar -f

			//Validar nombre archivo y guardarlo en nombre_archivo

		}

	}else{
		exit(0);
	}

	printf("\nCantidad de parametros %d" , argc );

	for (unsigned i=1; i< argc; i++) {
	    printf("\narg%d=%s", i, argv[i]);
	 }



}

