Trabajo práctico final EDyA1: The Travelling Salesman problem.

Alumno: Natalia Mellino.

Características del código:

-) Compilación y ejecución: para compilar utilizamos el comando: gcc -std=c99 -Wall -pedantic  main.c tsp.c
luego para ejecutar simplemente escribimos: ./a.out.

-) Estructuras elegidas para almacenar los datos:

Para almacenar los nombres de las ciudades se utilizó un arreglo del tipo char**, las ciudades se van almacenando al final del
arreglo a medida que se van leyendo. 
Luego para almacenar los costos entre las ciudades se optó por usar una matriz de enteros, donde las ciudades están representadas
por índices. Para asociar a cada ciudad con un índice hacemos uso del arreglo de char** donde guardamos sus nombres, de esta forma
si tenemos por ejemplo:

Ciudades: {a, b, c, d}

En la matriz de costos, en las posiciones (0,1) y (1,0) va a estar el costo entre las ciudades a y b, si es que existe alguno.
De esta forma logramos conectar las demás ciudades con sus respectivos costos.

Para almacenar la solución del TSP: utilizaremos un arreglo de enteros del tamaño cantCiudades+1, de esta forma si tenemos por
por ejemplo el arreglo de ciudades:

Ciudades: {a, b, c, d}

y en el arreglo solución tenemos: {0, 2, 3, 1, 0} esto nos índica que la solución son las ciudades:
a,c,d,b,a (a recorrer en ese orden), es decir, en el arreglo solución guardamos los índices de las ciudades correspondientes
al arreglo de Ciudades. De esta forma se facilita un poco al estar trabajando con enteros y no con char* en el algoritmo
de resolución del TSP. Ademas teniendo los índices almacenados en la solución, podemos acceder a los nombres de las ciudades de
forma inmediata sin necesidad de buscar en el arreglo todos los nombres.

-) Idea para el algoritmo de resolución del problema:

Queremos encontrar el mínimo camino que recorra todas las ciudades pasando una vez por cada una y vuelva
a la ciudad de inicio. Si queremos encontrar el menor camino de todos necesariamente tendremos que ver todos
los posibles caminos para así asegurarnos de que el que tenemos es efectivamente el más chico. 
El algoritmo propuesto sigue esta idea, pero se trató de optimizar en algunos aspectos para no explorar a fondo
TODAS las soluciones, ya que esto resulta muy costoso. La idea es la siguiente:

Arrancando desde la ciudad de inicio tomamos sus ciudades adyacentes y recursivamente buscamos si hay un camino
por dichas ciudades. Hay dos formas de las que podemos disminuir la cantidad de llamadas recursivas y evitar
explorar caminos innecesarios:
La primera, es llevar cuenta de las ciudades ya visitadas, si una de las ciudades adyacentes a la ciudad en la que
me encuentro ya fue visitada, podemos asegurar que no nos llevará a una solución válida.
La segunda forma de descartar caminos innecesarios es poniendo una cota superior, es decir, una vez que encontramos una
solución válida almacenamos el costo total de esa solución y seguimos explorando caminos (pues debemos ver si hay una mejor 
solucion). Si durante la exploración de un posible camino nos encontramos que el costo parcial que viene llevando ya supera
al costo de la mejor solución encontrada hasta el momento, podemos también descartar este camino y dejar de explorarlo,
ya que de ser un camino válido su costo sera mayor al del mejor camino que tenemos (hasta ahora), y podemos directamente 
descartarlo.
En resumen el algoritmo sigue esta idea: si ya recorrí todas la ciudades, verifico si estoy en una solución válida. Si es
válida y además es mejor que la que ya tengo, la reemplazo y esta pasa a ser la mejor solución.
Si no terminé de recorrer todas las ciudades, empiezo a buscar un camino, desde la ciudad en la que estoy actualmente,
llamando recursivamente a la función para recorrer todas las ciudades adyacentes a la ciudad en la que estoy actualmente,
siempre y cuando la ciudad adyacente no haya sido visitada y el costo de la solución parcial no supere al costo de la mejor
solución.