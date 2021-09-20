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
void mergeSort(int* A, int p, int r);
void merge(int* A, int p, int q, int r);
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
	int num; //Lee un número del archivo

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
	for(i=0; i<n; i++){
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
	mergeSort(A, 0, n-1);
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

/*Descripción:
	mergeSort ordena un arreglo de números dividiendo ese arreglo en arreglos cada vez más
	pequeños hasta lograr arreglos de un elemento, para luego ordenar dichos arreglos más fácilmente.
*/
void mergeSort(int* A, int p, int r){
	int q;
	if(p < r){
		q = (p+r)/2; // Se divide el arreglo en la mitad entera a la izquieda.
		mergeSort(A, p, q); // Se divide el arreglo en la mitad izquierda.
		mergeSort(A, q+1, r); // Se divide el arreglo en la mitad derecha.
		merge(A, p, q, r); // Se ordenan las mitades.
	}
}


/*Descripción:
	Merge es la función que se encarga de comparar y unir los subarreglos generados por 
	mergeSort, es aquí donde se obtiene el arreglo ordenado.
*/
void merge(int* A, int p, int q, int r){
	int l=r-p+1, i=p, j=q+1, k, m;
	/* 	l: tamaño del subarreglo C
		i: inicio del primer arreglo C en A.
		j: inicio del segundo arreglo C en A.
		k: contador para ciclos for.
		m: contador de C para guardar los valores ordenados en el arreglo A.
	*/
	int *C = (int*)malloc((l)*sizeof(int));
	// C es el arreglo temporal de valores ordenados.

	// Se hace un ciclo para cada subarreglo de A.
	for(k=0; k<l; k++){
		// i y j avanzan para comparar a cada elemento dentro del subarreglo.
		if(i<=q && j<=r){
			//Aquí se compara los elementos para determinar donde está el más pequeño.
			if(A[i] < A[j]){
				C[k] = A[i];
				i++;
			}else{
				C[k] = A[j];
				j++;
			}
		}else{
			//Por otro lado, cuando i o j llegan al final del subarreglo, el ciclo inserta todos los elementos 
			//restantes restante en C.
			if(i<=q){
				C[k] = A[i];
				i++;
			}else{
				C[k] = A[j];
				j++;
			}
		}
	}
	// Debido a que al terminar los contextos, los arreglos C desaparecen, los elementos ordenados son remplazados
	// dentro del arreglo A.
	m = 0;
	for(k=p; k<=r; k++){
		A[k] = C[m];
		m++;		
	}
}

