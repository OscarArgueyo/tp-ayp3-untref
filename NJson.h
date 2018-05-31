#ifndef __NJSON_H__
#define __NJSON_H__


/**
 * Definiciones de los TDA de la solución
 **/

/**
 * Definicion del TDA NJson
 **/
typedef struct _nJson{
	char* nombre;
	struct _dato* dato;
} NJson;


/**
 *
 * Definicion del TDA Dato
 **/
typedef struct _dato{
	char* nombre;
	void* valor;
	unsigned longArray;
	struct _dato* sig;
	void* (*func)(void*);
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
 * sizeDato: tama�o del tipo de dato.
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
	void* (*func)(void*)
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
	void* (*func)(void*)
);

/**
 * Primitiva de impresion del njson
 *
 **/
void njson_print(NJson* this);

/**
 * Primitiva de guardado de la impresion del njson como string en un archivo destino
 */
unsigned int njson_tofile(NJson* this , char* filename);


/**
 * Primitiva de impresion del tipo de dato: Entero
 **/
void njson_imprimir_entero(void* valor);

/**
 * Primitiva de impresion del tipo de dato: Entero sin signo
 **/
void njson_imprimir_unsigned(void* valor);

/**
 * Primitiva de impresion del tipo de dato: Double
 **/
void njson_imprimir_double(void* valor);

/**
 * Primitiva de impresion del tipo de dato: Flotante
 **/
void njson_imprimir_float(void* valor);

/**
 * Primitiva de impresion del tipo de dato: String
 **/
void njson_imprimir_string(void* valor);

/**
 * Primitiva de impresion del tipo de dato: Boolean
 **/
void njson_imprimir_boolean(void* valor);


/**
Primitivas de la entrega 3
*/

Dato* njson_obtener_dato(NJson* this, char* clave);

void njson_cambiar_contenido(
    NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*)
);

/**
 * Fin Primitivas del NJson
 */































 /**
 * Otras Primitivas //Avanzando el TP los vamos a usar o modificar
 * char * njson_tostring(NJson* this);
 * void njson_print(NJson* this);
 *
 * void njson_agregar(NJson* njson, const char* clave, void* value);
 * int njson_existe_clave(NJson* njson, const char* clave);
 * Valor* njson_obtener_clave(NJson* njson, const char* clave);
 * void njson_eliminar_clave(NJson* njson, const char* clave);
 * void njson_liberar(NJson* njson);
 * char* escribir(char* string, NJson* this);
 * void escribir_entero(char* string, void* valor);
 * void escribir_ensigned(char* string, void* valor);
 * void escribir_double(char* string, void* valor);
 * void escribir_float(char* string, void* valor);
 * void escribir_string(char* string, void* valor);
 * void escribir_bolean(char* string, void* valor);
 */

// Documentar todas las primitivas

#endif // __NJSON_H__

