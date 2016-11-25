#include "estructuras.h"
#ifndef _FUNCIONES_H
#define _FUNCIONES_H

/*
 * Funcion existFile
 * funcion que verifica si un archivo de texto plano existe
 * @param char* filename, nombre del archivo
 * @return entero 1 en caso de que si exista y 0 en caso contrario
*/
int 	existsFile 				(char* filename);

/*
 * Funcion rtrim
 * funcion que elimina todos los caracteres de espacio (" ") al final de un string
 * @param char* string, string a modificar
*/
void 	rtrim 					(char* string);

/*
 * Funcion inicializarMatrizAdy
 * funcion que inicializa una matriz de enteros
 * @param int vertices, numero de filas y columnas que tendra la matriz
*/
int** 	inicializarMatriz 		(int dimension);

/*
 * Funcion showMatriz 
 * funcion que muestra por consola una matriz
 *@param int** matriz, int vertices, matriz es la matriz a mostrary vertices la cantidad de filas y columnas de ella
*/
void 	showMatriz				(int** matriz,int dimension);

/*
 * Funcion inicializarImagen
 * funcion que inicializa una imagen con cantidad de filas y columnas igual a dimension entregada
 * @param int dimension, refiere a la dimension de la imagen (dimension x dimension), "imagen cuadrada"
 * @return punter a la estructura Imagen inicializada
*/

Imagen* inicializarImagen		(int dimension);
/*
 * Funcion showImagen
 * funcion que muestra por pantalla las caracteristicas de la imagen
 * @param Imagen* imagen, puntero a estructura Imagen la cual sera detallada en pantalla
*/
void 	showImagen				(Imagen* imagen);
/*
 * Funcion actualizarInfo
 * funcion que actualiza la informacion de una imagen, esto quiere decir
 * que actualiza la uniformidad, como tambien el minimo y maximo numero de la matriz de la imagen
 * @param Imagen* imagen, puntero a imagen a la cual se le actualizaran los datos
*/
void 	actualizarInfo			(Imagen* imagen);
/*
 * Funcion destruirImagen
 * funcion que destruye o libera una imagen
 * @param Imagen* imagen, puntero a imagen la cual sera liberada de memoria.
*/
void 	destruirImagen			(Imagen* imagen);
/*
 * Funcion createImagen
 * funcion que crea una imagen a partir de un archivo de texto
 * @param char* nameFile, cadena de texto con el nombre del archivo
 * @return Imagen*, puntero a imagen creada.
*/
Imagen*	createImagen			(char* nameFile);
/*
 * Funcion inicializarArbol
 * funcion que inicializa una estructura de arbol, pidiendo memoria para este
 * @return Arbol* , puntero a estructura Arbol 
*/
Arbol* 	inicializarArbol		();
/*
 * Funcion cargarImagenArbol 
 * funcion que agrega en un arbol una imagen entregaada
 * @param  Arbol* arbol, Imagen* imagen, puntero a Arbol y a imagen.
*/
void 	cargarImagenArbol		(Arbol* arbol,Imagen* imagen);
/*
 * Funcion particionarArbol
 * funcion que particiona un arbol y agrega 4 hijos de este con sus respectivas imagenes particionadas
 * @param Arbol* arbol, puntero a arbol el cual se particionara
*/
void 	particionarArbol		(Arbol* arbol);
/*
 * Funcion marcar
 * funcion deja marcado con un numero una imagen las casillas de una matriz correspondientes al arbol entregado
 * @param Arbol* hoja, Imagen* imagen, int* id. hoja refiere a un putnero a arbol el cual se analizara y marcara 
 * dentro de la matriz de la imagen con el numero entregado a traves de paso por refenrecia en id.
 * 
*/
void 	marcar 					(Arbol* hoja,Imagen* imagen,int* id);
/*
 * Funcion marcarGrupos 
 * funcion que marca los los grupos de los hijos de un arbol, en la matriz de la imagen entregada,
 * en otras palabras fuciona todas las particiones que cumplen con la condicion
 * @param Arbol* arbol, int condicion, int* id, Imagen* imagen. arbol refiere al arbol a analizar,
 * condicion refiere a la condicion que deben cumplir para funcionarse las partes, id refiere al numero
 * con el cual se marcara el grupo dentro de la matriz de la imagen entregada.
*/
void 	marcarGrupos 			(Arbol* arbol, int condicion,int* id,Imagen* imagen);
/*
 * Funcion uniformidadDosImagenes
 * funcion que entrega la uniformidad si esque se unen dos imagenes.
 * @param Imagen* img1,Imagen* img2, donde img1 e img2 refieren a las iamgenes a analizar
 * @return entero con el valor de la uniformidad calculada.
*/
int 	uniformidadDosImagenes 	(Imagen* img1,Imagen* img2);
/*
 * Funcion uniformidadTresImagenes
 * funcion que entrega la uniformidad si esque se unen tres imagenes.
 * @param Imagen* img1,Imagen* img2,Imagen* img3, donde img1, img2 e img3 refieren a las iamgenes a analizar
 * @return entero con el valor de la uniformidad calculada entre las 3 imagenes.
*/
int 	uniformidadTresImagenes	(Imagen* img1,Imagen* img2,Imagen* img3);
/*
 * Funcion particionMasiva
 * funcion que particiona recursivamente los arboles contetidos en un arbol si esque no se cmple la condicion 
 * de uniformidad entregada.
 * @param Arbol* arbol, int condicion,int* id,Imagen* imagen, donde arbol es el arbol a trabajar, int condicion
 * refiere a la condicion que se evaluara para decidir si se particiona el arbol o imagen, id refiere al numero
 * con el cual se marcaran los grupos encontrados que cumplen con la condicion, por ultimo imagen refiere
 * a la imagen en la cual se marcaran los grupos encontrados.
*/
int 	particionMasiva			(Arbol* arbol, int condicion,int* id,Imagen* imagen);
/*
 * Funcion esHoja
 * funcion que verifica si un arbol es hoja, esto quiere decir que no tiene hijos
 * @param Arbol* arbol, puntero a arbol el cual se analizara
*/
int 	esHoja					(Arbol* arbol);
/*
 * Funcion recorrido
 * funcion que recorre un arbol y va mostrando los datos contenidos en el
 * @param Arbol* arbol, arbol que se recorrera
*/
void 	recorrido				(Arbol* arbol);
/*
 * Funcion esNumero
 * funcion que verifica si un string es un numero valido
 * @param char* numero, cadena de caracteres el cual se verificara
 * @return int, 1 en aso de ser un numero valido, 0 en caso de ser caulquier otra cosa no valida.
*/
int 	esNumero				(char* numero);
/*
 * Funcion titulo
 * funcion que imprime en pantalla el titulo del programa
*/
void 	titulo					();
/*
 * Funcion crearArchivo 
 * funcion para guardar el resultado del programa, esto quiere decir que crea un archivo con el nombre 
 * ingresado en el cual guarda lo que esta en la matriz de la imagen (resultado)
 * @param Imagen* imagen, char* nameFile, imagen refiere a la imagen del resultado, nameFile refiere al
 * nombre con el cual e guardara el archivo.
*/
void 	crearArchivo			(Imagen* imagen,char* nameFile);












#endif