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
//int busquedaFibonacci(int* array, int x, int n);
void fibonacci(int *arrayFibonacci);
int busquedaFibonacci(int *array, int *arrayFibonacci,int n,int x);
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
	if (argc!=3) 
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
	int arrayFibonacci[37];
    fibonacci(arrayFibonacci);
    int posicion = busquedaFibonacci(array, arrayFibonacci, n, m);
    printf("%i ",posicion);
    //int posicion = busquedaFibonacci(array, 0, n-1, m);
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
  .
*/

void fibonacci(int* arrayFibonacci){
    arrayFibonacci[0]=0;
    arrayFibonacci[1]=1;
    for(int i=2; i < 37; i++){
        arrayFibonacci[i] = arrayFibonacci[i-1] + arrayFibonacci[i-2];
    }
}

int min(int a, int b){
    if(a>b){
        return b;
    }
    return a;
}

int busquedaFibonacci(int* array, int* arrayFibonacci,int n, int x){
    int fbM1,fbM2,fbM;
    int i=0;
    while(arrayFibonacci[i]<n){
        i++;
    }
    fbM = arrayFibonacci[i];
    fbM1 = arrayFibonacci[i-1];
    fbM2 = arrayFibonacci[i-2];

    int offset = -1;

    while(fbM > 1){
        int j = min(offset + fbM2, n - 1);
        if(array[j] < x){
            fbM  = fbM1;
            fbM1 = fbM2;
            fbM2 = fbM - fbM1;
            offset = j;
        }
        else{
            if (array[j] > x){
                fbM  = fbM2;
                fbM1 = fbM1 - fbM2;
                fbM2 = fbM - fbM1;
            }
            else{
                return j;
            } 
        } 
    }

    if (fbM1 && array[offset + 1] == x){
        return offset + 1;
    }
        
    return -1;
}