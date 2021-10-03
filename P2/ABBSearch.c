//*****************************************************************
//Cerón Jiménez Pedro Eduardo 
//Curso: Análisis de algoritmos
//Algoritmo de busqueda: Arbol Binario de Busqueda (ABB search)
//(C) Septiembre 2021
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
struct nodo{
	int contenido;
	struct nodo *ptrIzq;
	struct nodo *ptrDer;
};
struct nodo *crearNodo(int datoEnt){
	struct nodo *ptrNuevo=(struct nodo *)malloc(sizeof(struct nodo));
	ptrNuevo->contenido=datoEnt;
	ptrNuevo->ptrIzq=NULL;
	ptrNuevo->ptrDer=NULL;
	return ptrNuevo;
}
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void insertar(struct nodo **, int);
int busqueda(struct nodo *, int);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int i; //Variables de los loops
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int *a; //variable para crear el arreglo
	int n;//controla el numero de argumentos
	int num;//asigna los valores introducidos al arreglo
	int x[]={322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //variable para el valor a buscar	
	struct abb *ptrRaizBase=NULL; //puntero para la raiz base del arbol
	struct abb **ptrRaiz; //puntero que se movera por el arbol
	ptrRaiz=&ptrRaizBase; //asignamos el puntero que se mueve al arbol a la base del mismo
	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) {
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaÃ±o del algoritmo
	else{
		n=atoi(argv[1]);
	}
	//******************************************************************	
	//Inicialización de los arreglos.
	a = (int*) malloc(sizeof(int)*n); //encargada del arreglo de los elementos

	// Se inicializa el arreglo desordenado.
	// Los números en desorden se obtendrán de un archivo de texto.
	for(i=0; i<=n-1; i++){  //Se asignan los datos de entrada al arreglo 
		scanf("%d",&num);
		a[i]=num;
	}
//************Insertamos los numeros en el arreglo	
	for(i=0;i<n;i++){
		insertar(ptrRaiz,a[i]);
	//printf(".:%d\n",a[i]);	//corroboramos que a tenga los argumentos. 
	}
	for(i=0;i<20;i++){
		//printf(".:Numero a buscar = %d :.\n",x[i]);	//unicamente para saber que se tiene el numero a buscar
		//printf(".:Tamaño n = %d :.\n",n);
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
		busqueda(*ptrRaiz,x[i]);	//funcion de busqueda con el puntero de la raiz y el dato a encontrar
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
}
	//Terminar programa normalmente	
	exit (0);	
}
//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
// insertamos en el arbol
void insertar(struct nodo **ptrRaiz,int datoEnt){
/*	Funcion para introducir elementos dentro de un abol binario de busqueda.
	Al primer dato en introducir se le realiza la creacion de un nuevo nodo para iniciar el arbol, mientras que los demas elementos
	por ingresar al arbol se hará mediante la comparacion de si es mayor o menor al elemento que se encuentre en arbol para así ingresarlo
	ya sea por el lado izquierdo (en caso de ser menor) o por el lado derecho (en caso de ser mayor) del arbol	*/
	if(*ptrRaiz==NULL){
		*ptrRaiz=crearNodo(datoEnt);
	}
	else if(((*ptrRaiz)->contenido)>datoEnt){
		insertar(&((*ptrRaiz)->ptrIzq),datoEnt);
	}else{
		insertar(&((*ptrRaiz)->ptrDer),datoEnt);
	}
}
int busqueda(struct nodo *ptrRaiz, int datoBusq){
/*	Funcion para buscar un elemento dentro de un arbol binario de busqueda.
	Primeramente se realiza la comparacion para verificar que haya al menos un dato dentro del arbol (raiz)
	y en caso de existir se realiza la comparacion en busca del elemento, en caso de no ser la raiz el elemento a buscar se realiza una comparacion
	para saber si es mayor o menor al elemento que se encuentra en dicho nodo del arbol, dependiedno el caso, los punteros se moveran por la parte
	derecha o izquierda del nodo para nuevamente realizar la busqueda, el ciclo se realiza hasta encontrar el elemento o llegar al final del arbol	*/

	while (ptrRaiz!=NULL){	//ciclo para seguir buscando mientras no se llegue al final del arbol
		if(datoBusq==ptrRaiz->contenido){	//verificamos si el dato que buscamos esta en la raiz
				//printf(".:Dato Encontrado =%f.:\n",datoBusq);	//unicamente para saber si lo encontramos
				return (datoBusq);	//retornamos el dato que buscabamos y esta en el arreglo
		}else if(datoBusq<ptrRaiz->contenido){	//checamos si el dato a encontrar es menor al contenido de la raiz
				ptrRaiz=ptrRaiz->ptrIzq;	//en caso de ser cierto, nuestra raiz ahora sera la parte izquierda, eliminando la derecha
			}else
				ptrRaiz=ptrRaiz->ptrDer;	//caso contrario, la raiz sera la parte derecha, eliminando la izquierda
	}
		//printf(".:Dato no encontrado:.\n");	//unicamente para corroborar que no sea haya encontrado el dato en todo el arbol
}
