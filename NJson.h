/**
 * @brief Archivo NJson.h con declaracion de los TDA y las firmas de las primitivas del Trabajo Práctico Final 
 * 
 * @file NJson.h
 * @author Argueyo Oscar, Diaz Alan
 * @date 2018-06-29
 */
#ifndef __NJSON_H__
#define __NJSON_H__

/**
 * Definiciones de los TDA de la solución
 **/

/**
 * @brief Definicion del TDA NJson
 **/
typedef struct _nJson{
	char* nombre;
	struct _dato* dato;
} NJson;


/**
 * @brief Definicion del TDA Dato
 **/
typedef struct _dato{
	char* nombre;
	void* valor;
	unsigned longArray;
	unsigned sizeDato;
	struct _dato* sig;
	void* (*func)(void*,FILE*,unsigned);
} Dato;


/**
 * Inicio de primitivas del NJSON, DATO e impresiones de datos
 **/

/**
 * Primitiva de inicializacion del njson
 * this: NJson a incializar.
 * nombre: nombre del NJson.
 * nombreDato: nombre del primer dato.
 * valor: valor del primer dato.
 * sizeDato: tamaï¿½o del tipo de dato.
 * array: si es o no un array.
 * longArray: longitud del array.
 * func: puntero a la funcion que escribe el dato.
 */
NJson* njson_init(
	NJson* this,
	char* nombre,
	char* nombreDato,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
);


/**
 * Primitiva que libera la memoria allocada del Njson
 **/
void njson_release(NJson* this);

/**
 * Primitiva de liberacion de la memoria dinamica allocada para los tipos de datos almacenados en el json
 **/
void njson_dato_release(Dato* this);

void njson_dato_agregar(
	NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
);

Dato* njson_agregar_siguiente_dato(
	Dato* dato, 
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
);


void njson_print(NJson* this, FILE* out, unsigned opcion);


unsigned int njson_tofile(NJson* this , char* filename);


void njson_imprimir_entero(void* valor, FILE* out, unsigned opcion);


void njson_imprimir_unsigned(void* valor, FILE* out, unsigned opcion);


void njson_imprimir_double(void* valor, FILE* out, unsigned opcion);


void njson_imprimir_float(void* valor, FILE* out, unsigned opcion);


void njson_imprimir_string(void* valor, FILE* out, unsigned opcion);


void njson_imprimir_boolean(void* valor, FILE* out, unsigned opcion);


void njson_imprimir_array(Dato* dato, FILE* out, unsigned opcion);


int njson_obtener_dato(NJson* this, char* clave, Dato** dato);

void njson_cambiar_contenido(
    NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
);


void njson_dato_escribir(Dato* dato, FILE* out, unsigned opcion);

#endif // __NJSON_H__

