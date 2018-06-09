#ifndef __NJSON_H__
#define __NJSON_H__


/**
 * Definiciones de los TDA de la soluciÃ³n
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

/**
 * Primitiva de impresion del njson
 *
 **/
void njson_print(NJson* this, FILE* out, unsigned opcion);

/**
 * Primitiva de guardado de la impresion del njson como string en un archivo destino
 */
unsigned int njson_tofile(NJson* this , char* filename);


/**
 * Primitiva de impresion del tipo de dato: Entero
 **/
void njson_imprimir_entero(void* valor, FILE* out, unsigned opcion);

/**
 * Primitiva de impresion del tipo de dato: Entero sin signo
 **/
void njson_imprimir_unsigned(void* valor, FILE* out, unsigned opcion);

/**
 * Primitiva de impresion del tipo de dato: Double
 **/
void njson_imprimir_double(void* valor, FILE* out, unsigned opcion);

/**
 * Primitiva de impresion del tipo de dato: Flotante
 **/
void njson_imprimir_float(void* valor, FILE* out, unsigned opcion);

/**
 * Primitiva de impresion del tipo de dato: String
 **/
void njson_imprimir_string(void* valor, FILE* out, unsigned opcion);

/**
 * Primitiva de impresion del tipo de dato: Boolean
 **/
void njson_imprimir_boolean(void* valor, FILE* out, unsigned opcion);


/**
 * Primitiva de impresion de arrays de datos
 **/
void njson_imprimir_array(Dato* dato, FILE* out, unsigned opcion);


/**
Primitivas de la entrega 3
*/

/**
Obtenemos el dato de un njson a partir de la clave
*/
int njson_obtener_dato(NJson* this, char* clave, Dato** dato);

/**
Cambiamos el contenido de un elemento del njson a partir de la clave
*/
void njson_cambiar_contenido(
    NJson* this,
	char* nombre,
	void* valor,
	unsigned sizeDato,
	unsigned longArray,
	void* (*func)(void*,FILE*,unsigned)
);

/**
Escribimos el dato del json en el archivo definido en out
*/
void njson_dato_escribir(Dato* dato, FILE* out, unsigned opcion);

/**
 * Fin Primitivas del NJson
 */
#endif // __NJSON_H__

