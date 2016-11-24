#ifndef _STRUCTS_H_
#define _STRUCTS_H_





typedef struct imagen{
	int** matriz;
	int dimension;
	int uniformidad;
	int min;
	int max;

}Imagen;

typedef struct arbol{
	Imagen* imagen;
	struct arbol* hijos[4];
	int fil;
	int col;

}Arbol;





#endif