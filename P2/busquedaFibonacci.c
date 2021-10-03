//*****************************************************************
//CIPRIANO DAMIAN SEBASTIAN
//Curso: Análisis de algoritmos
//(C) Septiembre 2021
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//Algoritmo: BUSQUEDA FIBONACCI
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
int min(int a, int b);
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
	int arrayFibonacci[37]; //Arreglo para guardar los primeros 37 numeros de la secuencia de fibonacci
	int x[]={322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //variable para el valor a buscar	
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

	int *array = (int*)malloc(n*sizeof(int));

    for(i = 0; i < n; i++){
        scanf("%d", &num);
        array[i] = num;
    }
	
	//******************************************************************	

	float t1=0,t2=0,t3=0,cpu=0;
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
    fibonacci(arrayFibonacci);
	for(int i=0; i < 20 ;i++){
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);
		//******************************************************************
		//******************************************************************	
		//Algoritmo
		//******************************************************************	
		int res =  busquedaFibonacci(array, arrayFibonacci, n, x[i]);
		printf("%i ", res);
		//******************************************************************

		//******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		printf("\nPARA EL VALOR:%i\n",x[i]);
		uswtime(&utime1, &stime1, &wtime1);
		//Cálculo del tiempo de ejecución del programa
		t1+= wtime1 - wtime0;
		t2+= utime1 - utime0;
		cpu+=(utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0);
		t3+=stime1 - stime0;
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
	t1 = t1/20;
	t2 = t2/20;
	t3 = t3/20;
	cpu = cpu/20;
	//Mostrar los tiempos promedio de ejecución
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  t1);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  t2);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  t3);
	printf("CPU/Wall   %.10f %% \n",100.0 * cpu);
	printf("\n");
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
//Descriptcion de Fibonacci.
/*
  Esta función retorna los primeros 37 elementos de la sucesion de fibonacci.
  Tienen que ser esa cantidad debido a que la posicion 37 de la sucesion de fibonacci
  es 14930352 que es el número fibonacci mas pequeño justo mayor que 10000000. 
*/

void fibonacci(int* arrayFibonacci){
	//Valores auxiliares para calcular los elementos de la sucesion de fibonacci
    arrayFibonacci[0]=0;
    arrayFibonacci[1]=1;
	/*Mediante la tecnica de programación dinamica conocida como memoizacion,
	es como podemos calcular eficientemente los primeros 37 elementos de la sucesion de fibonacci */
    for(int i=2; i < 37; i++){
        arrayFibonacci[i] = arrayFibonacci[i-1] + arrayFibonacci[i-2];
    }
}

//Descriptcion de Min.
/*
  Esta función retorna el más pequeño de dos elementos a y b.
  Si ambos son equivalentes, una se devuelve.
*/

int min(int a, int b){
    if(a>b){
        return b;
    }
    return a;
}

//Descriptcion de Busqueda Fibonacci.
/*
	La busqueda de Fibonacci es un algoritmo de busqueda para un elemento x dentro de un arreglo.
	La búsqueda de Fibonacci es un algoritmo de búsqueda de intervalo eficiente.
	Al igual que la busqueda binaria, necesita el arreglo ordenado.
	Se llama búsqueda de Fibonacci porque utiliza la serie de Fibonacci.
*/

int busquedaFibonacci(int* array, int* arrayFibonacci,int n, int x){
	//fbM es el numero de fibonacci mas pequeño justo mayor o igual que el tamaño del arreglo.
	//fbM1 y fbM2 son los inmediatos predecesores de fbM.
    int fbM1,fbM2,fbM;
    int i=0;
	/*Este ciclo permite encontrar el numero de fibonacci mas pequeño
	justo mayor o igual que el tamaño del arreglo y sus predecesores. */
    while(arrayFibonacci[i]<n){
        i++;
    }
	//Asignamos valores a fbM, fbM1 y fbM2.
    fbM = arrayFibonacci[i];
    fbM1 = arrayFibonacci[i-1];
    fbM2 = arrayFibonacci[i-2];

	//Iniciamos el desplazamiento en -1.
    int desplazamiento = -1;

    while(fbM > 1){
        int j = min(desplazamiento + fbM2, n - 1);
        if(array[j] < x){
			/*Si X es mayor que este elemento, descartamos la mitad antes de este elemento y
			movemos la secuencia de Fibonacci un paso hacia atrás. Este paso descarta el tercio frontal del espacio de búsqueda del array.*/
            fbM  = fbM1;
            fbM1 = fbM2;
            fbM2 = fbM - fbM1;
            desplazamiento = j;
        }
        else{ /*Si X es más pequeño que este elemento, descartamos la mitad después de este elemento y movemos la secuencia de Fibonacci dos pasos hacia atrás.
			 Además, actualizamos el desplazamiento para cambiar el índice de inicio del espacio de búsqueda. Estos pasos descartan los dos tercios posteriores del espacio de búsqueda del array.*/
            if (array[j] > x){
                fbM  = fbM2;
                fbM1 = fbM1 - fbM2;
                fbM2 = fbM - fbM1;
            }
            else{ /*Si X es igual a este elemento, devolvemos el índice.*/
                return j;
            } 
        } 
    }
	//Si fbM1 es igual a 1 tenemos un elemento sin marca. Si X es igual a este elemento, devolvemos el índice.
    if (fbM1 == 1 && array[desplazamiento + 1] == x){
        return desplazamiento + 1;
    }
    //En caso de no encontrar el elemento, tenemos que retornar -1.
    return -1;
}