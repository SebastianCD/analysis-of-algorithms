//*****************************************************************
//CARDELAS GONZÁLEZ JOANTHAN
//Curso: Análisis de algoritmos
//(C) Septiembre 2021
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//ALgoritmo: BUSQUEDA EXPONENCIAL
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
int busquedaExponencial(int* arreglo, int inicio, int final, int numero);
int menor(int a, int b);
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
	int num; //Numero leido del archivo

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

	int *array = (int*)malloc(n*sizeof(int)); // Se crea el arreglo donde se almacenarán los números ordenados.

	int x[]={322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //variable para el valor a buscar	

    for(i = 0; i < n; i++){ // Se llena el arreglo con números ordenados.
        scanf("%d", &num);
        array[i] = num;
    }

	for(i = 0; i < 20; i++){
		printf("Se busca a %d.\n", x[i]);
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);
		//******************************************************************
		
		//******************************************************************	
		//Algoritmo
		//******************************************************************	
		int posicion = busquedaExponencial(array, 0, n-1, x[i]);
		//******************************************************************

		//******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);

		//Resutados del algoritmo.
		printf("Esta en la posicion %d\n", posicion);
		
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

/*
    Descripción: La busqueda exponencial divide el arreglo original en subarreglos dados por arreglo[2^i...2^(i+1)], i = 0, 1, 2, 3, ...
    Una vez encontrado el subarreglo donde se encuentra el número buscado, se procede a hacer la búsqueda binaria en dicho subarreglo.

    arreglo: es el arreglo completo inicial.
    inicio: es el index del primer elemento del arreglo.
    final: es el index del último elemento de arreglo.
    numero: es el número buscado.
    
    Consideraciones: el arreglo original debe estar ordenado de menor a ma

*/

int busquedaExponencial(int* arreglo, int inicio, int final, int numero){
    //Preguntamos si el número buscado se encuentra en la primera localidad.
    if(arreglo[0] == numero)
        return 0;
    //Si no, comienza la búsqueda exponencial.

    int i = 1; //2^0 es igual a 1 que es el comienzo de la búsqueda exponencial.
    while(i < final && arreglo[i] <= numero) //Preguntamos si el indice es menor que el final y si el valor del arreglo en el indice es menor que el número buscado.
        i = i*2; //En caso de ser verdad, aumentamos la exponencial en 1.

    return busquedaBinaria(arreglo, i/2, menor(i, final), numero); //Una vez que se deje de cumplir el while, tendremos el rango donde se encuentra el número buscado.
}

/*
    Descripción: esta función devuelve el menor de dos números enteros.
    a: primer número.
    b: segundo número.
*/

int menor(int a, int b){
    return (a<b)?a:b;
}

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