#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NJson.h"

#define NAME_MAX 255 // Largo máximo para nombre de archivos en linux.
int main(int argc, char* argv[]) {

	NJson njson;
	NJson* pnjson;
	pnjson = njson_init(&njson);

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
	}
}

