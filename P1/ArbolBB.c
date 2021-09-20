//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************
struct abb{
	int dato;
	struct abb *der;
	struct abb *izq;
};
//creamos el arbol
struct abb *crearNodo(int n_entrada){
	struct abb *ptrNuevo=(struct abb *)malloc(sizeof(struct abb));
	ptrNuevo->dato=n_entrada;
	//los punteros de derecha e izquierda se les asignan NULL para no tener un dato aleatorio
	ptrNuevo->der=NULL;
	ptrNuevo->izq=NULL;
	
	return ptrNuevo;
}
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void insertar(struct abb **, int);
void inorden(struct abb *);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	struct abb *ptrRaizBase=NULL;
	struct abb **ptrRaiz;
	ptrRaiz=&ptrRaizBase;
	int n; //n determina el tamaño del algorito dado por argumento al ejecutar
	int i; //Variables para loops
	int num; //Lee un número del archivo
	int midato;
	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	n=atoi(argv[1]);
	
	//******************************************************************	
	//Inicialización de los arreglos.
	int *A = (int*)malloc(n*sizeof(int)); //Arreglo desordenado.

	// Se inicializa el arreglo desordenado.
	// Los números en desorden se obtendrán de un archivo de texto.
	for(i=0; i<n-1; i++){
		scanf("%d", &num);
		A[i] = num;
		midato=A[i];
	}

	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
		insertar(ptrRaiz,num);
		inorden(*ptrRaiz);
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);
	
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
// insertamos en el arbol
void insertar(struct abb **ptrRaiz, int n_entrada){
	//if para saber si hay un dato en la raiz del arbol, en caso de que no exissta nada, se crea el arbol
	if(*ptrRaiz==NULL){
		*ptrRaiz=crearNodo(n_entrada);
	//si hay un dato en la raiz se hacen las comparaciones para saber en que lado de la raiz estara nuestro dato	
	}else if(((*ptrRaiz)->dato)>n_entrada){	//si el dato es mayor al numero de entrada se guardara en el lado izquierdo del arbol
		insertar(&((*ptrRaiz)->izq),n_entrada);
	}else{									//si el dato es menor al numero de entrada se guardara en el lado derecho del arbol
		insertar(&((*ptrRaiz)->der),n_entrada);
	}
}
//se hace el recorrido INORDER para asi entregar los valores ordenados
void inorden(struct abb *ptrRaiz){
	if(ptrRaiz!=NULL){
		inorden(ptrRaiz->izq);
		//printf(" %d \n",ptrRaiz->dato);
		inorden(ptrRaiz->der);
	}
}


