#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"
#define MAX_ARR 20
#define MAX_CAD 30

// Algoritmo que resuelve el problema del viajante. Recibe:

// -La matriz de costos,
// -Dos arreglos de enteros: 'mejorSol' y 'solParcial' donde se guardan la mejor
// solución hasta el momento y la solución que estoy explorando.
// (respectivamente).
// -Dos punteros a int donde se almacena el costo de la mejor solución y el de
// la solución actual.
// -Arreglo de visitados: consiste en un arreglo de enteros donde se marcan con
// 1 las ciudades que ya fueron visitadas y 0 las que no lo fueron. Para saber
// si una ciudad fue visitada o no, basta consultar si el arreglo de visitados
// en el índice correspondiente a la ciudad es un 0 o un 1. Por ejemplo, si mi
// arreglo de ciudades es: {a,b,c,d}, y quiero saber si b ya fue visitada, basta
// con preguntar si visitados[1] es igual a 1. (1 es el índice que ocupa b en el
// arreglo de ciudades).
// -Dos enteros que representan: uno la cantidad de ciudadades, otro la ciudad
// actual en la que estoy (posActual) y uno que indica cuantas ciudades llevo
// recorriendo ya (nivel).

void resolver_tsp(int** matriz, int visitados[], int solParcial[],
                  int mejorSol[], int* costoMejor, int* costoParcial, int nivel,
                  int cantCiudades, int posActual) {
  if (nivel == cantCiudades) {
    // Terminé de visitar todas las ciudades, debo verificar si tengo una
    // solución.
    if (matriz[0][posActual] > 0) {
      if ((*(costoParcial) + matriz[0][posActual] < *(costoMejor) ||
           *(costoMejor) == 0)) {
        // Encontré una mejor solucion, la copio en mejorSol.
        for (int i = 0; i < cantCiudades; i++) {
          mejorSol[i] = solParcial[i];
        }
        mejorSol[nivel] = mejorSol[0];
        *(costoMejor) = *(costoParcial) + matriz[0][posActual];
      }
    }
  }

  else {
    for (int i = 0; i < cantCiudades; i++) {
      if (*(costoParcial) < *(costoMejor) || *(costoMejor) == 0) {
        if (visitados[i] == 0 && matriz[posActual][i] > 0) {
          // Marco la ciudad como visitada y la agrego a la solución parcial.
          visitados[i] = 1;
          solParcial[nivel] = i;
          *(costoParcial) += matriz[posActual][i];
          // Llamo recursivamente a la función para ver si seguir por este
          // camino, me lleva a una solución.
          resolver_tsp(matriz, visitados, solParcial, mejorSol, costoMejor,
                       costoParcial, nivel + 1, cantCiudades, i);
          // Desmarco como visitada la casilla para seguir buscando una solución
          // mejor (si es que hay) en la siguiente ciudad.
          visitados[i] = 0;
          *(costoParcial) -= matriz[posActual][i];
        }
      }
    }
  }
}

// Llamamos a la función que resuelve el tsp para el mapa dado y escribimos su
// solución en un archivo.

void tsp(Ciudades listaCiudades, int** matrizCostos, char* archivoSalida) {
  int visitados[listaCiudades->elems], solParcial[listaCiudades->elems + 1],
      mejorSol[listaCiudades->elems + 1];
  if (listaCiudades->elems > 1) {
    // Inicializamos el arreglo de ciudades visitadas y los arreglos donde
    // guardaremos la solución parcial y la mejor solución.

    for (int i = 0; i < listaCiudades->elems; i++) {
      visitados[i] = 0;
      mejorSol[i] = -1;
      solParcial[i] = -1;
    }
    mejorSol[listaCiudades->elems] = -1;
    solParcial[listaCiudades->elems] = -1;

    // Variables donde almacenamos el costo de la mejor solución y el costo de
    // la solución parcial.

    int *costoMejor, *costoParcial, cm = 0, cp = 0;
    costoMejor = &cm;
    costoParcial = &cp;

    // Agrego el ínidce de la ciudad de inicio (tomamos arbritariamente la
    // primera) y la marco como visitada.

    visitados[0] = 1;
    solParcial[0] = 0;

    // Llamamos a la función que encuentra la solución y la escribimos en un
    // archivo.

    resolver_tsp(matrizCostos, visitados, solParcial, mejorSol, costoMejor,
                 costoParcial, 1, listaCiudades->elems, 0);
    escribir_solucion(archivoSalida, mejorSol, listaCiudades, matrizCostos,
                      *(costoMejor));
    printf("Archivo de salida generado.\n");
  } else {
    printf(
        "El mapa no contiene la cantidad de ciudades necesarias\npara generar "
        "un recorrido. Pruebe con otro mapa.\n");
  }
}

int main(int argc, char* argv[]) {
  int** matrizCostos;
  Ciudades ciudades = crear_ciudades();
  char entrada[MAX_CAD], salida[MAX_CAD];
  strcpy(entrada, argv[1]);
  strcpy(salida, argv[2]);
  strcat(entrada, ".txt");
  strcat(salida, ".txt");
  // Leemos el archivo de entrada y guardamos las ciudades y costos.
  matrizCostos = leer_entrada(entrada, ciudades);
  // Resolvemos el TSP y liberamos la memoria utilizada.
  tsp(ciudades, matrizCostos, salida);
  destruir_matriz(matrizCostos, ciudades->elems);
  destruir_ciudades(ciudades);
  return 0;
}