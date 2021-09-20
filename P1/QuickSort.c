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

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void intercambiar(int* A, int i, int j);
void quickSort(int*A, int p, int r);
int pivot(int *A, int p, int r);
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
	int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
	int i; //Variables para loops

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
	else
	{
		n=atoi(argv[1]);
	}
	
	int *A = (int*)malloc(n*sizeof(int)), num;
	
	for(i = 0; i < n; i++){
		scanf("%d", &num);
		A[i] = num;
	}

	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	quickSort(A, 0, n-1);
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
/*
Descripción:
	El quicksort es un algoritmo de ordenamiento donde por medio de la selección de un pivote
	se crean subarreglos, donde se vuelve a seleccionar un pivote para cada subarreglo y así ordenar
	cada uno de ellos hasta su minima expresión, un miniarreglo ordenado de 1 elemento.
*/
void quickSort(int*A, int p, int r){ //Se recibe A que es el arreglo desordenado, p que es el inicio del dicho arrelo y r que es el final.
	int j;
	if(p<r){ //Verificamos que el inicio no sea mayor al final.
		j = pivot(A, p, r); //j es el pivote que ordena al arreglo que empieza en p y termina en r
		quickSort(A, p, j-1); //Recursivamente se ordena el subarreglo que empieza en p y termina en j-1
		quickSort(A, j+1, r); //Recursivamente se ordena el subarreglo que empieza en j+1 y termina en r
	}
}

/*
Descripción:
	Pivot es la función que se encarga de mover los elemntos menores al pivote al lado izquiedo y
	los elementos mayores al pivote al lado derecho. Cuando ya movió todos los elementos, esta devuelve
	la posición del pivote.
*/

int pivot(int *A, int p, int r){ //Se recibe A que es el arreglo desordenado, p que es el inicio del dicho arrelo y r que es el final.
	int piv = A[p]; //Se toma como pivote al primer elemento dentro del arreglo[p -> r]
	int i = p+1; //Se empieza a comparar a partir del siguiente elemento después del pivote.
	int j = r; //Se empieza a comparar a partir del último elemento en el arrelo[p -> r]
	do{
		while(A[i] < piv && i<r){// Se busca desde el inicio un elemento que no sea menos que el pivote.
			i++;
		}
		while(A[j]>piv && j>p){// Se busca desde el final un elemento que no sea mayor que el pivote.
			j--;
		}
		
		if(i<j){// Si i<j, quiere decir que aun quedan elementos por ordenar.
			intercambiar(A, i, j);
			//impArray(A, p, r);
			i++; j--;
		}
		else{// Si i no es menor que j, quiere decir que solo falta mover al pivote.
			intercambiar(A, p, j);
			//impArray(A, p, r);
			i++; j--;
			return j+1; //Cuando el pivote se mueva, se regresa el indice del pivote que es j + 1.
		}
	}while(i<r && j>p);
}

/*
Descripción:
	Se intercambian los valores del arreglo A. El valor de la posición i se guarda en la posición j y viceversa.
*/

void intercambiar(int* A, int i, int j){ //Se recibe A que es el arreglo, i donde esta el primer valor y j donde está el segundo valor.
	int temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}