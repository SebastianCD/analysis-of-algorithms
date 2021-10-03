//*****************************************************************
//Cedillo Sanchez Karolina
//Curso: Análisis de algoritmos
//(C) Septiembre 2021
//ESCOM-IPN
//Medición de tiempo en C y recepción de parametros en C bajo UNIX 
//para el algoritmo de búsqueda lineal.
//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tiempo.h"
#define tam 20
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
int busqueda (int *A, double b, int n);
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char *argv[])
{
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos.
	int n; //Tamaño del arreglo.
	int i; //Variables de los iteradores.
	int num; //Valor tomado del archivo.
	double B[]={322486,14700764,3128036,6337399,61396,10399545,2147445644,1295390003,450057883,187645041,1980098116,152503,5000,1493283650,214826,18433449527,1360803954,210924866,2147470852,0};//Números a búscar.
	int res; //Resultado de la búsqueda.
	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	else
	{
		//Tomar el segundo argumento como tamaño del algoritmo
		n = atoi(argv[1]);
	}
	// Generar el arreglo de tamaño n
	int * A = (int*) malloc(sizeof(int)*n); 
	// Se llena el algoritmo con los valores del arreglo.
	for(i=0; i<n;i++)
	{
		scanf("%d",&num);
		A[i]=num;
	}
	for(i=0;i<tam; i++)
	{
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);
		//******************************************************************
		//******************************************************************	
		//Algoritmo
		//******************************************************************	
		res =  busqueda (A, B[i], n);
		printf("%i ", res);
		//******************************************************************

		//******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		printf("\nPARA EL VALOR:%0.1f\n",B[i]);
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
	}
		//Terminar programa normalmente	
		exit (0);	
}
//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
//Descripción de búsqueda líneal.
/*
 Este método búsca el elemento de forma secuencial, es decir, va de posición a posición 
 de forma secuencial. 
 Cuando se encuentra el valor, se retorna su posición, si el valor no es encontrado se retorna -1.
 En el siguiente algoritmo se muestra la búsqueda secuencial, sin embargo, para hacerlo más eficiente
 se parte de la primera y última posición del arreglo hacia el centro, para 
 retornar la posición.
*/
int busqueda (int *A, double b, int n)
{
	int izquierda=0;//Auxiliar al inicio.
	int posicion=-1;//Posición inicial.
	int derecha= n-1;//Auxiliar al final.
	while( izquierda <= derecha && posicion==-1)//Se repite el ciclo hasta que ambos auxiliares queden al centro del arreglo o ya se haya encontado la posición.
	{
		if(A[izquierda] == b)//Encuentra al elemento por la izquierda del arreglo.
		{
			posicion=izquierda;//D la posición en el arreglo del elemento encontrado.
		}
		else { if (A[derecha] == b)//Encuentra al elemento por la derecha del arreglo.
			posicion = derecha;//Da la posición en el arreglo del elemento encontrado.		
		}
		//Se avanzan a los auxiliares por el arreglo.
		izquierda++;
		derecha--;
	}
	
	if(posicion == -1)
		posicion = -1;//Se retorna en caso de que no se haya encontrado al elemento.
	return posicion;
	
}



