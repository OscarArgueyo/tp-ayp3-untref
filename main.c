/**
 * @brief Archivo main para la generacion de un JSON de prueba para testeo de los TDA creados. 
 * 
 * @file main.c
 * @author your name
 * @date 2018-06-30
 */
#include <string.h>
#include <stdlib.h>
#include "NJson.h"

#define NAME_MAX 255 // Largo maximo para nombre de archivos en linux.

/**
 * @brief Metodo main de verificacion de creación del njson para imprimirlos por consola o guardar el json generado en un archivo, si se pasaron las opciones correctas.
 * 
 * @param argc 
 * @param argv 
 */
void main(int argc, char* argv[]) {

	NJson njson;
	NJson contents;
	NJson photoInfo;

	/**
	 * Declaracion del puntero al nombre del archivo si lo necesitamos segun
	 * opciones de ejecucion
	 */
	char* nombre_archivo[NAME_MAX];

	/**
	 * Declaracion de variables a guardarse en el json para probar el funcionamiento
	 */

	//photo_info
	float latLong[2] = {37.77256666666666, -122.45934166666667};
	char* timeTaken = "Wed, 28 Aug 2013 18:12:02 +0000";
	njson_init(&photoInfo,"photo","lat_long",latLong,sizeof(latLong),2,(void*)&njson_imprimir_float);
	njson_dato_agregar(&photoInfo,"time_taken",timeTaken,strlen(timeTaken)+1,0,(void*)&njson_imprimir_string);

	//contents
	char* size = "2.3 MB";
	char* rev = "38af1b183490";
	char thumbExists = '1';
	unsigned bytes = 2453963;
	char* modified = "Mon, 07 Apr 2014 23:13:16 +0000";
	char* clientMtime = "Thu, 29 Aug 2013 01:12:02 +0000";
	char* path = "/Photos/flower.jpg";
	char isDir = '0';
	char* icon = "page_white_picture";
	char* root = "dropbox";
	char* mimeType = "image/jpeg";
	unsigned revision = 14511;

	njson_init(&contents,"contents","size",size,strlen(size)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"rev",rev,strlen(rev)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"thumb_exists",&thumbExists,sizeof(char),0,(void*)&njson_imprimir_boolean);
	njson_dato_agregar(&contents,"bytes",&bytes,sizeof(unsigned),0,(void*)&njson_imprimir_unsigned);
	njson_dato_agregar(&contents,"modified",modified,strlen(modified)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"client_mtime",clientMtime,strlen(clientMtime)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"path",path,strlen(path)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"photo info",&photoInfo,sizeof(NJson),0,(void*)&njson_print);
	njson_dato_agregar(&contents,"is_dir",&isDir,sizeof(char),0,(void*)&njson_imprimir_boolean);
	njson_dato_agregar(&contents,"icon",icon,strlen(icon)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"root",root,strlen(root)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"mime_type",mimeType,strlen(mimeType)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&contents,"revision",&revision,sizeof(unsigned),0,(void*)&njson_imprimir_unsigned);

	NJson arrayContents[1] = {contents};

	//njson
	char* sizeJson = "0 bytes";
	char* hashJson = "37eb1ba1849d4b0fb0b28caf7ef3af52";
	unsigned bytesJson = 0;
	char thumbExistsJson = '0';
	char* revJson = "714f029684fe";
	char* modifiedJson = "Wed, 27 Apr 2011 22:18:51 +0000";
	char* pathJson = "/Photos";
	char isDirJson = '1';
	char* iconJson = "folder";
	char* rootJson = "dropbox";
	unsigned revisionJson = 29007;

	njson_init(&njson,"njson","size",sizeJson,strlen(sizeJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"hash",hashJson,strlen(hashJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"bytes",&bytesJson,sizeof(unsigned),0,(void*)&njson_imprimir_unsigned);
	njson_dato_agregar(&njson,"thumb_exists",&thumbExistsJson,sizeof(char),0,(void*)&njson_imprimir_boolean);
	njson_dato_agregar(&njson,"rev",revJson,strlen(revJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"modified",modifiedJson,strlen(modifiedJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"path",pathJson,strlen(pathJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"is_dir",&isDirJson,sizeof(char),0,(void*)&njson_imprimir_boolean);
	njson_dato_agregar(&njson,"icon",iconJson,strlen(iconJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"root",rootJson,strlen(rootJson)+1,0,(void*)&njson_imprimir_string);
	njson_dato_agregar(&njson,"contents",arrayContents,sizeof(NJson),1,(void*)&njson_print);
	njson_dato_agregar(&njson,"revision",&revisionJson,sizeof(unsigned),0,(void*)&njson_imprimir_unsigned);

	//Tomamos las opciones ingresados por la terminal
	//Ejecutando ./programa -f [nombre_archivo] para generar un archivo con nombre [nombre_archivo] con el json generado 
	//Ejecutando ./programa imprime el njson en la terminal.
	if	(argc == 3 || argc == 1){
		//Podemos avanzar
		if(argc == 1){ //No tenemos parametros OK
			//njson_print(pnjson);
			njson_print(&njson,NULL,0);
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
	njson_release(&photoInfo);
	njson_release(&contents);
	njson_release(&njson);

}//Fin main

