/*
 * nJson.h
 */

#ifndef __NJSON_H__
#define __NJSON_H__

typedef struct _Clave{
	char* clave;
} Clave;

typedef union _Valor
{
    Boolean bool;
    NJson njson;
    Entero entero;
    String string;
    Array array;
} Valor;

typedef struct _Boolean{
	/**
	 * Se puede hacer de mil formas posibles
	 */
}Boolean;

typedef struct _Entero{
	int valor;
}Entero;

typedef struct _String{
	char* valor;
}String;

typedef struct _Array{

	void* valor;
	/**
	 * Este es el complicado
	 */
}Array;


typedef struct _NJson{
	Clave* clave;
	Valor* valor;
	NJson* sig;

	/**
	 * El NJson en el que se inicializa pero al mismo
	 * tiempo es un valor posible para las claves del json
	 * Se puede manejar como un diccionario de python.
	 */

} NJson;


/**
 * Inicio Primitivas del NJson
 */

NJson* njson_init();

/**
 * Entrega 1
 */
char * njson_tostring(NJson* this);
void njson_print(NJson* this);
unsigned int njson_tofile(NJson* this , char* filename);
/**
 * Fin Entrega 1
 */

void njson_agregar(NJson* njson, const char* clave, void* value);
int njson_existe_clave(NJson* njson, const char* clave);
Valor* njson_obtener_clave(NJson* njson, const char* clave);
void njson_eliminar_clave(NJson* njson, const char* clave);
void njson_liberar(NJson* njson);


/**
 * Fin Primitivas del NJson
 */

/**
 * Otras Primitivas
 */

// Documentar todas las primitivas
#endif // __NJSON_H__


