//*****************************************************************
//M. EN C. EDGARDO ADRI�N FRANCO MART�NEZ 
//Curso: An�lisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medici�n de tiempo en C y recepci�n de parametros en C bajo UNIX
//Compilaci�n: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementaci�n de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecuci�n: "./main n" (Linux y MAC OS)
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
//DECLARACI�N DE FUNCIONES
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
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medici�n de tiempos
	int n; //Tama�o del arreglo tomado desde su ejecuci�n
	int num;

	//******************************************************************	
	//Recepci�n y decodificaci�n de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecuci�n y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tama�o del algoritmo
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
	
	shell(a,n);  //Llamada a la funci�n de ordenamiento shell
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecuci�n 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);
	
	//C�lculo del tiempo de ejecuci�n del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acci�nes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acci�nes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICI�N DE FUNCIONES 
//************************************************************************

void shell (int *a,int n)
{
	k=trunc(n/2); //saber el tama�o de la mitad del arreglo
	while(k>=1){ //verificar que no es el final del ordenamiento
		b=1;
			while(b!=0){
				b=0;
					for(i=k;i<n-1;i++){ //verifica que haya m�s numeros por ordenar
						if(a[i-k]>a[i]){ //compara cada par de numeros segun el turno del ordenamiento
//mueve el elemento peque�o a la variable temporal y el elemento grande al lugar que ocupaba el elemento peque�o
							temp=a[i];	
							a[i]=a[i-k];
							a[i-k]=temp;
//mueve el elemento peque�o de la variable temporal al lugar que ocupaba el elemento grande
							b=b+1;
						}
					}
			}
		k=trunc(k/2); //cuando es el final del ordenamiento divide para obtener el entero a 0 y as� indicar que se ha terminado el ordenamiento
	}
/*	for(i=0;i<n-1;i++)
	printf(".:%d \n",a[i]);
*/
}
