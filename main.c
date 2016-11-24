#include "funciones.h"
#include "estructuras.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){




	Arbol* arbol=NULL;
	Imagen* imagen=NULL;
	Imagen* salida=NULL;
	int criterio;
	int id = 0;
	titulo();
	char nameFile[255];
	int opcion=0;
	do{
		printf("1) Cargar imagen desde un archivo.\n");
		printf("2) Mostrar imagen cargada.\n" );
		printf("3) Crear arbol segun criterio de uniformidad. \n");
		printf("4) Mostrar recorrido del arbol.\n");
		printf("5) Mostrar regiones uniformes de la imagen.\n");
		printf("6) Guardar archivo con las regiones uniformes de la imagen.\n");
		printf("7) Salir.\n");

		printf("\nIngrese una opcion: ");
		fflush(stdin);
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				
				memset(nameFile,'0',255);
				//char stringBuffer[LARGOLINE];
				printf("\nIngrese el nombre de un archivo: ");
				scanf("%s", nameFile);
				
				if (existsFile(nameFile)){
					if(imagen!=NULL){
						destruirImagen(imagen); 
					}
					imagen=(Imagen*)createImagen(nameFile);
					printf("Imagen cargada\n\n");
					
				}
				else{
					printf("El archivo ingresado no existe\n\n");
				}
				break;
			case 2:
				//printf("Mostrar grafo conexo\n");
				if(imagen!=NULL){
					printf("\n");
					showImagen(imagen);
					printf("\n");
				}
				else{
					printf("\nNo existe ninguna imagen cargado\n\n");
				}
				
				break;

			case 3:
				//printf("verificar grafo conexo\n");
				if(imagen!=NULL){
					char buffer[255];
					printf("\nIngrese criterio de uniformidad: ");
					scanf("%s", buffer);
					if (esNumero(buffer)){
						criterio = atoi(buffer);
						arbol=(Arbol*)inicializarArbol();
						cargarImagenArbol(arbol, imagen);
						salida= (Imagen*) inicializarImagen(imagen->dimension);
						particionMasiva(arbol,criterio,&id,salida);
						printf("Arbol creado utilizando criterio de uniformidad %d.\n\n",criterio );
						//printf("uniformidad : %d \n",uniformidadTresImagenes(arbol->hijos[1]->imagen,arbol->hijos[2]->imagen,arbol->hijos[3]->imagen));
												
					}
					else{
						printf("\nCaracter ingresado invalido.\n\n");
					}
						
				}
				else{
					printf("\nSe necesita cargar una imagen previamente.\n\n");
				}
				
				break;
			case 4:
				if (arbol!=NULL){
					recorrido(arbol);
					printf("\n");
				}
				else{
					printf("\nNo existe ningun arbol creado.\n\n");
				}
				break;
			case 5:
				if (salida!=NULL){
					printf("\nCriterio de uniformidad aplicado: %d\n\n",criterio );
					showMatriz(salida->matriz,salida->dimension);
					printf("\n");
				}
				else{
					printf("\nSe necesita cargar un arbol previamente.\n\n");
				}
				break;
			case 6:
				if (salida!= NULL){
					char nombre[255];
					char valor[200];
					
					printf("\nIngrese un nombre para el archivo sin extencion: ");
					fflush(stdin);
					scanf("%s", nombre);
					strcpy(nombre ,strcat(nombre,".txt"));
					if (existsFile(nombre)){
						do{
							printf("El archivo ya existe, desea sobreescribir? (s/n): " );
							fflush(stdin);		
							scanf("%s", valor);
							if(strcmp(valor,"s") && strcmp(valor,"S") && strcmp(valor,"n") && strcmp(valor,"N")){
								printf("Respuesta incorrecta\n");
							}
						}while(strcmp(valor,"s") && strcmp(valor,"S") && strcmp(valor,"n") && strcmp(valor,"N"));

						if (!strcmp(valor,"s") || !strcmp(valor,"S")){
							crearArchivo(salida,nombre);
							printf("El archivo ha sido guardado.\n\n");
						}
						else{
							printf("El archivo NO ha sido guardado.\n\n");
						}
						
					}
					else{
						crearArchivo(salida,nombre);
						printf("El archivo ha sido guardado.\n\n");
					}
					
					
					
				}
				else{
					printf("Se necesita crear un arbol.\n\n");
				}

				break;
			

		}
	}while(opcion!=7);
	printf("El programa ha finalizado.\n");
	



	return 0;	
}