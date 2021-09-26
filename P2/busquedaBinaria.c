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
int busquedaBinaria(int* array, int inicio, int final, int numero);
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
	int num; //Valor tomado del archivo
	int m; //Valor buscado
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
		m=atoi(argv[2]);
	}

	int *array = (int*)malloc(n*sizeof(int));

    for(i = 0; i < n; i++){
        scanf("%d", &num);
        array[i] = num;
    }
	
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	int posicion = busquedaBinaria(array, 0, n-1, m);
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
    Descripción: La busqueda binaria se basa en dividir el arreglo por la mitad, preguntandose si el número buscado
    está en la mitad izquieda o mitad derecha, haciendo esto hasta encontrar el número buscado o hasta acabar con
    todo el arreglo.
    array: arreglo de enteros ordenados.
    inicio: es el primer index del arreglo 'array'
    final: es el último index del arreglo 'array'
    numero: es el valor buscado dentro del arreglo 'array'

    Consideraciones: el rango dado por inicio y final, debe contener a la totalidad de elementos del arreglo, ya que
    los que estén fuera de este rango no serán buscados.
    Además, el arreglo 'array' debe estar ordenado de menor a mayor.
*/
int busquedaBinaria(int* array, int inicio, int final, int numero){
    int medio; //Este será el término medio que separará a los dos subarreglos.

    while(inicio <= final){
        medio = (inicio + final)/2; //Se calcula el elemento central del arreglo.

        if(array[medio] == numero) //Preguntamos si el valor con index m es el valor buscado.
            return medio; // Si el valor medio es el valor buscado, entonces se devuelve el index de dicho valor y termina la función.

        if(numero < array[medio]) //Preguntamos si el valor buscado está del lado izquiedo.
            final = medio - 1; // Si el número buscado es menor que el valor medio, entonces se toma la parte izquieda del arreglo.

        if(numero > array[medio]) //Preguntamos si el valor buscado está del lado derecho.
            inicio = medio + 1; // Si el númeor buscado es mayor que el valor medio, entonces se toma la parte derecha del arrelgo.
    }

    return -1; // Si el arreglo es recorrido en su totalidad y no se encontró el valor buscado, quiere decir que este
               // no se encuentra dentro del arreglo.
}