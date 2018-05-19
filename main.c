#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NJson.h"

#define NAME_MAX 255 // Largo máximo para nombre de archivos en linux.
int main(int argc, char* argv[]) {

	NJson njson;
	char* escritura = 0x0;

	unsigned valorUnsigned = 55;
	int valorInteger = 8;
	double valorDouble = 11.28;
	float valorFlotante = 15.12;
	char valorBoleano = 1;
	char* valorString = "714f129684fe";

	njson_init(&njson,"PruebaJson","numero1 unsigned",&valorUnsigned,sizeof(unsigned),0,1,escribirUnsigned);
	agregarDato(njson.dato,"numero2 integer",&valorInteger,sizeof(int),0,1,escribirEntero);
	agregarDato(njson.dato,"numero3 double",&valorDouble,sizeof(double),0,1,escribirDouble);
	agregarDato(njson.dato,"numero4 float",&valorFlotante,sizeof(float),0,1,escribirFloat);
	agregarDato(njson.dato,"boolean",&valorBoleano,sizeof(char),0,1,escribirBoolean);
	agregarDato(njson.dato,"texto",valorString,strlen(valorString)+1,0,1,escribirString);
	agregarDato(njson.dato,"numero3 otra vez",&valorDouble,sizeof(double),0,1,escribirDouble);
	agregarDato(njson.dato,"boolean otra vez",&valorBoleano,sizeof(char),0,1,escribirBoolean);
	agregarDato(njson.dato,"numero4 otra vez",&valorFlotante,sizeof(float),0,1,escribirFloat);

	//escribir(escritura,&njson);

	//printf("%s",escritura);

	//njson_release(&njson);

	char* nombre_archivo[NAME_MAX];

	if	(argc == 3 || argc == 1){//Podemos avanzar
		if(argc == 1){ //No tenemos parametros
			//njson_print(pnjson);
			escribir(escritura,&njson);
		}

		if(argc == 3){ //Tenemos dos parametros -f y nombre archivo

			if (strcmp(argv[1], "-f") == 0 && strlen(argv[2]) <= NAME_MAX){
				*nombre_archivo = argv[2];
				njson_tofile(&njson , *nombre_archivo);

			}//Validar -f

			//Validar nombre archivo y guardarlo en nombre_archivo
		}
		njson_release(&njson);
	}else{
		njson_release(&njson);
		exit(0);
	}

}

