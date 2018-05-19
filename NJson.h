
#ifndef __NJSON_H__
#define __NJSON_H__

typedef struct _nJson{
	char* nombre;
	struct _dato* dato;
} NJson;

typedef struct _dato{
	char* nombre;
	void* valor;
	char array;
	unsigned longArray;
	struct _dato* sig;
	void* (*func)(char*,void*);
} Dato;

/*
 * this: NJson a incializar.
 * nombre: nombre del NJson.
 * nombreDato: nombre del primer dato.
 * valor: valor del primer dato.
 * sizeDato: tamaño del tipo de dato.
 * array: si es o no un array.
 * longArray: longitud del array.
 * func: puntero a la funcion que escribe el dato.
 */
NJson* njson_init(NJson* this, char* nombre, char* nombreDato, void* valor,
		unsigned sizeDato, char array, unsigned longArray, void* (*func)(char*,void*));

void njson_release(NJson* this);
void dato_release(Dato* this);

Dato* agregarDato(Dato* this, char* nombre, void* valor, unsigned sizeDato,
		char array, unsigned longArray, void* (*func)(char*,void*));

char* escribir(char* string, NJson* this);
void escribirEntero(char* string, void* valor);
void escribirUnsigned(char* string, void* valor);
void escribirDouble(char* string, void* valor);
void escribirFloat(char* string, void* valor);
void escribirString(char* string, void* valor);
void escribirBoolean(char* string, void* valor);
unsigned int njson_tofile(NJson* this , char* filename);

/*
char * njson_tostring(NJson* this);
void njson_print(NJson* this);
unsigned int njson_tofile(NJson* this , char* filename);


void njson_agregar(NJson* njson, const char* clave, void* value);
int njson_existe_clave(NJson* njson, const char* clave);
Valor* njson_obtener_clave(NJson* njson, const char* clave);
void njson_eliminar_clave(NJson* njson, const char* clave);
void njson_liberar(NJson* njson);
*/

/**
 * Fin Primitivas del NJson
 */

/**
 * Otras Primitivas
 */

// Documentar todas las primitivas

#endif // __NJSON_H__


