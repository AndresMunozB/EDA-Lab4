#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
/*
 * Funcion existsFile
*/
int existsFile(char* filename) {
	FILE* f = NULL;
	f = fopen(filename,"r");
	if (f == NULL) 
		return 0;
	else {
		fclose(f);
		return 1;
	}
	return 0;
}

/*
 * Funcion rtrim
*/
void rtrim(char* string){
	while(string[strlen(string)-1]==' ' 
		|| string[strlen(string)-1]=='\n' 
		|| string[strlen(string)-1]=='\t'
		|| string[strlen(string)-1]=='\r'){
		string[strlen(string)-1]='\0';
	}
}

/*
 * Funcion inicializarMatriz
*/
int** inicializarMatriz(int dimension){
	int** matriz=(int**)malloc(sizeof(int*)*dimension);
	int i,j;
	for (i=0;i<dimension;i++){
		matriz[i]=(int*)malloc(sizeof(int*)*dimension);
	}
	for (i=0;i<dimension;i++){
		for (j=0;j<dimension;j++){
			matriz[i][j]=-1;
		}
	}
	return matriz;
}

/*
 * Funcion showMatriz
*/
void showMatriz(int** matriz,int dimension){
	int i,j;
	for (i=0;i<dimension;i++){
		for (j=0;j<dimension;j++){
			printf("%d ",matriz[i][j] );
		}
		printf("\n");
	}
}
/*
 * Funcion inicializarImagen
*/
Imagen* inicializarImagen(int dimension){
	Imagen* imagen= (Imagen*) malloc(sizeof(Imagen));
	imagen->matriz=inicializarMatriz(dimension);
	imagen->dimension=dimension;
	imagen->uniformidad=0;
	imagen->min=0;
	imagen->max=0;
}
/*
 * Funcion showImagen
*/
void showImagen(Imagen* imagen){
	printf("Uniformidad: %d\n",imagen->uniformidad );
	printf("Dimension: %d\n",imagen->dimension );
	printf("Matriz: \n");
	showMatriz(imagen->matriz,imagen->dimension);
}

/*
 * Funcion actualizarInfo
*/
void actualizarInfo(Imagen* imagen){
	imagen->min=imagen->matriz[0][0];
	imagen->max=imagen->matriz[0][0];
	int i,j;
	for (i=0;i<imagen->dimension;i++){
		for (j=0;j<imagen->dimension;j++){
			if (imagen->min>imagen->matriz[i][j]){
				imagen->min=imagen->matriz[i][j];
			}
			if (imagen->max<imagen->matriz[i][j]){
				imagen->max=imagen->matriz[i][j];
			}
		}
	}
	imagen->uniformidad=imagen->max-imagen->min;
	//printf("%d\n",imagen->uniformidad );
}
/*
 * Funcion destruirImagen
*/
void destruirImagen(Imagen* imagen){
	int i;
	for (i=0;i<imagen->dimension;i++){
		free(imagen->matriz[i]);
	}
	free(imagen->matriz);
	free(imagen);
}
/*
 * Funcion createImagen
*/
Imagen* createImagen(char* nameFile){

	int buffer;
	int dimension;
	//printf("string:%s\n",nameFile );
	FILE* file=fopen(nameFile,"r");
	if(file==NULL){
		//printf("soy nulo\n");
	}
	fscanf(file,"%d",&dimension);
	Imagen* imagen=(Imagen*)inicializarImagen(dimension);
	int i,j;
	//printf("dimension: %d\n",dimension );
	for (i=0;i<dimension;i++){
		for (j=0;j<dimension;j++){
			fscanf(file,"%d",&buffer);
			//printf("%d\n",buffer );
			imagen->matriz[i][j]=buffer;
		}
	}
	//showImagen(imagen);
	actualizarInfo(imagen);
	return imagen;
	fclose(file);
}


/*
 * Funcion inicializarArbol
*/
Arbol* inicializarArbol(){
	Arbol* arbol=(Arbol*)malloc(sizeof(Arbol));
	arbol->imagen=NULL;
	arbol->hijos[0]=NULL;
	arbol->hijos[1]=NULL;
	arbol->hijos[2]=NULL;
	arbol->hijos[3]=NULL;
	arbol->fil=-1;
	arbol->col=-1;
	return arbol;
}
/*
 * Funcion cargarImagenArbol
*/
void cargarImagenArbol(Arbol* arbol,Imagen* imagen){
	arbol->imagen=imagen;
	arbol->fil=0;
	arbol->col=0;
}

/*
 * Funcion particionarArbol
*/
void particionarArbol(Arbol* arbol){


	arbol->hijos[0]= inicializarArbol();
	arbol->hijos[1]= inicializarArbol();
	arbol->hijos[2]= inicializarArbol();
	arbol->hijos[3]= inicializarArbol();
	//printf(" hola: %d \n",esHoja(arbol) );

	int dimension= arbol->imagen->dimension;
	Imagen* img0 = inicializarImagen(dimension/2);
	Imagen* img1 = inicializarImagen(dimension/2);
	Imagen* img2 = inicializarImagen(dimension/2);
	Imagen* img3 = inicializarImagen(dimension/2);

	//Rellenando las imagenes de adentro
	int i,j;
	for (i=0;i<dimension/2;i++){
		for(j=0;j<dimension/2;j++){
			img0->matriz[i][j]=arbol->imagen->matriz[i][j];
			img1->matriz[i][j]=arbol->imagen->matriz[i][j+dimension/2];
			img2->matriz[i][j]=arbol->imagen->matriz[i+dimension/2][j];
			img3->matriz[i][j]=arbol->imagen->matriz[i+dimension/2][j+dimension/2];
		}
		
	}
	//actualizar la informacion de las imagenes
	actualizarInfo(img0);
	actualizarInfo(img1);
	actualizarInfo(img2);
	actualizarInfo(img3);

	//cargar las imagenes en los arboles
	cargarImagenArbol(arbol->hijos[0],img0);
	cargarImagenArbol(arbol->hijos[1],img1);
	cargarImagenArbol(arbol->hijos[2],img2);
	cargarImagenArbol(arbol->hijos[3],img3);

	arbol->hijos[0]->fil = 0 + arbol->fil;
	arbol->hijos[1]->fil = 0 + arbol->fil;
	arbol->hijos[2]->fil = dimension/2 + arbol->fil;
	arbol->hijos[3]->fil = dimension/2 + arbol->fil;

	arbol->hijos[0]->col = 0 + arbol->col;
	arbol->hijos[1]->col = dimension/2 + arbol->col;
	arbol->hijos[2]->col = 0 + arbol->col;
	arbol->hijos[3]->col = dimension/2 + arbol->col;
	
	/*showImagen(arbol->hijos[0]->imagen);
	showImagen(arbol->hijos[1]->imagen);
	showImagen(arbol->hijos[2]->imagen);
	showImagen(arbol->hijos[3]->imagen);*/
}

/*
 * Funcion pintar
*/
void pintar(Arbol* hoja,Imagen* imagen,int* id){
	int i,j;
	int fil = hoja->fil;
	int col = hoja->col;
	for (i = 0 ; i < hoja->imagen->dimension ; i++){
		for (j = 0 ; j < hoja->imagen->dimension ; j++){
			imagen->matriz[i+fil][j+col] = *id;
		}
	}
}
/*
 * Funcion pintarGrupos
*/
void pintarGrupos(Arbol* arbol, int condicion,int* id,Imagen* imagen){
	if (uniformidadDosImagenes(arbol->hijos[0]->imagen,arbol->hijos[2]->imagen)<=condicion ){
		pintar(arbol->hijos[0],imagen,id);
		pintar(arbol->hijos[2],imagen,id);
		*id+=1;
	}
	if (uniformidadDosImagenes(arbol->hijos[1]->imagen,arbol->hijos[3]->imagen)<=condicion ){
		pintar(arbol->hijos[1],imagen,id);
		pintar(arbol->hijos[3],imagen,id);
		*id+=1;
	}
	if (uniformidadDosImagenes(arbol->hijos[0]->imagen,arbol->hijos[1]->imagen)<=condicion ){
		pintar(arbol->hijos[0],imagen,id);
		pintar(arbol->hijos[1],imagen,id);
		*id+=1;
	}
	if (uniformidadDosImagenes(arbol->hijos[2]->imagen,arbol->hijos[3]->imagen)<=condicion ){
		pintar(arbol->hijos[2],imagen,id);
		pintar(arbol->hijos[3],imagen,id);
		*id+=1;
	}

	if (uniformidadTresImagenes(arbol->hijos[0]->imagen,arbol->hijos[2]->imagen,arbol->hijos[3]->imagen)<=condicion ){
		pintar(arbol->hijos[0],imagen,id);
		pintar(arbol->hijos[2],imagen,id);
		pintar(arbol->hijos[3],imagen,id);	
		*id+=1;
	}
	if (uniformidadTresImagenes(arbol->hijos[0]->imagen,arbol->hijos[1]->imagen,arbol->hijos[3]->imagen)<=condicion){
		pintar(arbol->hijos[0],imagen,id);
		pintar(arbol->hijos[1],imagen,id);
		pintar(arbol->hijos[3],imagen,id);	
		*id+=1;
	}
	if (uniformidadTresImagenes(arbol->hijos[0]->imagen,arbol->hijos[1]->imagen,arbol->hijos[2]->imagen)<=condicion ){
		pintar(arbol->hijos[0],imagen,id);
		pintar(arbol->hijos[1],imagen,id);
		pintar(arbol->hijos[2],imagen,id);	
		*id+=1;
	}
	if (uniformidadTresImagenes(arbol->hijos[1]->imagen,arbol->hijos[3]->imagen,arbol->hijos[2]->imagen)<=condicion ){
		pintar(arbol->hijos[1],imagen,id);
		pintar(arbol->hijos[3],imagen,id);
		pintar(arbol->hijos[2],imagen,id);	
		*id+=1;
	}

}

/*
 * Funcion uniformidadDosImagenes
*/
int uniformidadDosImagenes (Imagen* img1,Imagen* img2){
	int max,min;
	if (img1->max>img2->max){
		max = img1->max;
	}
	else{
		max = img2->max;
	}
	if (img1->min<img2->min){
		min = img1->min;
	}
	else{
		min = img2->min;
	}
	return max-min;
}
/*
 * Funcion uniformidadTresImagenes
*/
int uniformidadTresImagenes(Imagen* img1,Imagen* img2,Imagen* img3){
	int max = img1->max;
	int min = img1->min; 
	if (max < img2->max){
		max = img2->max;
	}
	if (max < img3->max){
		max = img3->max;
	}
	if (min >img2->min){
		min = img2->min;
	}
	if (min >img3->min){
		min = img3->min;
	}
	return max-min;
}
/*
 * Funcion particionMasiva
*/
int particionMasiva(Arbol* arbol, int condicion,int* id,Imagen* imagen){

	if (arbol->imagen->uniformidad>condicion && arbol->imagen->dimension>1){
		particionarArbol(arbol);

		particionMasiva(arbol->hijos[0],condicion,id,imagen);
		particionMasiva(arbol->hijos[1],condicion,id,imagen);
		particionMasiva(arbol->hijos[2],condicion,id,imagen);
		particionMasiva(arbol->hijos[3],condicion,id,imagen);

		pintarGrupos(arbol,condicion,id,imagen);
		
	}
	else{
		if(esHoja(arbol)){
		pintar(arbol,imagen,id);
		*id+=1;
		}
	}
	return 1;

}

/*
 * Funcion esHoja
*/
int esHoja(Arbol* arbol){
	if (arbol == NULL){
		return 0;
	}
	if (arbol->hijos[0]==NULL &&
		arbol->hijos[1]==NULL &&
		arbol->hijos[2]==NULL &&
		arbol->hijos[3]==NULL)
	{
		return 1;
	}
	else {
		return 0;
	}
}

/*
 * Funcion recorrido
*/
void recorrido(Arbol* arbol){
	if (arbol==NULL){
		//printf("hola \n");
	}
	else if(esHoja(arbol)){
		showImagen(arbol->imagen);
		int fil = arbol->fil;
		int col = arbol->col;
	}
	else{
		showImagen(arbol->imagen);
		recorrido(arbol->hijos[0]);
		recorrido(arbol->hijos[1]);
		recorrido(arbol->hijos[2]);
		recorrido(arbol->hijos[3]);
	}
}

/*
 * Funcion esNumero
*/
int esNumero(char* numero){
    int num;
    num=atoi(numero); /* atoi convierte el numero ingresado como cadena en entero
    en caso de ser posible, de lo contrario retorna 0*/
    if(num!=0){
    	return 1;
    } 
    else{
    	return 0;
    }
}
       









