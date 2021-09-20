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
#include <math.h>
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
void shell(int *, int);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
	int i; //Variables de los loops
	int k;//define en cuantas partes se divide el arreglo y al final controla hasta donde se ordeno
	int b;//controla los ciclos while y for para el orden de los elementos
	int temp;//variable temporal para ordenar los elementos entre comparaciones
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char **argv)
{
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n; //Tamaño del arreglo tomado desde su ejecución
	int num;

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
		

	int *a = (int*) malloc(sizeof(int)*n); //encargada del arreglo de los elementos
	
	
	for(i=0; i<=n-1; i++)  //Se asignan los datos de entrada al arreglo 
	{
		scanf("%d",&num);
		a[i]=num;
	}		
	
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	
	shell(a,n);  //Llamada a la función de ordenamiento shell
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

void shell (int *a,int n)
{
	k=trunc(n/2); //saber el tamaño de la mitad del arreglo
	while(k>=1){ //verificar que no es el final del ordenamiento
		b=1;
			while(b!=0){
				b=0;
					for(i=k;i<n-1;i++){ //verifica que haya más numeros por ordenar
						if(a[i-k]>a[i]){ //compara cada par de numeros segun el turno del ordenamiento
//mueve el elemento pequeño a la variable temporal y el elemento grande al lugar que ocupaba el elemento pequeño
							temp=a[i];	
							a[i]=a[i-k];
							a[i-k]=temp;
//mueve el elemento pequeño de la variable temporal al lugar que ocupaba el elemento grande
							b=b+1;
						}
					}
			}
		k=trunc(k/2); //cuando es el final del ordenamiento divide para obtener el entero a 0 y así indicar que se ha terminado el ordenamiento
	}
/*	for(i=0;i<n-1;i++)
	printf(".:%d \n",a[i]);
*/
}
