#Arreglo con los números de prueba para la ejecución.
numerosPrueba=( 10 0 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

#Pruebas para Búsqueda Lineal
gcc BL.c tiempo.c -o BL.out
echo "Busqueda Lineal"
for numero in "${numerosPrueba[@]}";
do
    echo $numero >> BusquedaLineal.txt
    ./BL.out $numero < 10millones.txt >> BLRes.txt
done

#Pruebas para Árbol Binario de Busqueda
gcc ABBSearch.c tiempo.c -o abbsearch.out
echo "Busqueda Árbol Binario"
for numero in "${numerosPrueba[@]}";
do
    echo $numero >> ResultadosABBsearch.txt
    ./abbsearch.out $numero < 10millones.txt >> ResultadosABBsearch.txt
done


#Pruebas para Búsqueda binaria.
gcc busquedaBinaria.c tiempo.c -o busquedaBinaria.out
echo "Busqueda Binaria"
for numero in "${numerosPrueba[@]}";
do
    echo $numero >> ResultadosBusquedaBinaria.txt
    ./busquedaBinaria.out $numero < 10millones.txt >> ResultadosBusquedaBinaria.txt
done

#Pruebas para Búsqueda exponencial.
gcc busquedaExponencial.c tiempo.c -o busquedaExponencial.out
echo "Busqueda Exponencial"
for numero in "${numerosPrueba[@]}";
do
    echo $numero >> ResultadosbusquedaExponencial.txt
    ./busquedaExponencial.out $numero < 10millones.txt >> ResultadosbusquedaExponencial.txt
done

#Pruebas para Busqueda Fibonacci
gcc busquedaFibonacci.c tiempo.c -o busquedaFibonacci.out
echo "Busqueda Fibonacci"
for numero in "${numerosPrueba[@]}";
do
    echo $numero >> busquedaFibonacciResultados.txt
    ./busquedaFibonacci.out $numero < 10millones.txt >> busquedaFibonacciResultados.txt
done