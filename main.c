#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"
#define MAX_ARR 20
#define MAX_CAD 30

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
          // mejor en la siguiente ciudad.
          visitados[i] = 0;
          *(costoParcial) -= matriz[posActual][i];
        }
      }
    }
  }
}

void tsp(Ciudades listaCiudades, int** matrizCostos, char* archivoSalida) {
  int visitados[listaCiudades->elems], solParcial[listaCiudades->elems + 1],
      mejorSol[listaCiudades->elems + 1];

  // Inicializamos el arreglo de ciudades visitadas y los arreglos donde
  // guardaremos la solución parcial y la mejor solución.

  for (int i = 0; i < listaCiudades->elems; i++) {
    visitados[i] = 0;
    mejorSol[i] = -1;
    solParcial[i] = -1;
  }
  mejorSol[listaCiudades->elems] = -1;
  solParcial[listaCiudades->elems] = -1;

  // Variables donde almacenamos el costo de la mejor solución y el costo de la
  // solución parcial.

  int *costoMejor, *costoParcial;  // PONER TODO EN UNO.
  int cm = 0, cp = 0;
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
}

int main() {
  int** matrizCostos;
  Ciudades ciudades = crear_ciudades();
  char entrada[30], salida[30];
  // Pedimos los nombres de los archivos de entrada y salida, y guardamos los
  // datos.
  printf("Ingrese el nombre del archivo de entrada:\n");
  scanf("%s", entrada);
  strcat(entrada, ".txt");
  printf("Ingrese el nombre del archivo de salida:\n");
  scanf("%s", salida);
  strcat(salida, ".txt");
  matrizCostos = leer_entrada(entrada, ciudades);
  // Resolvemos el TSP y liberamos la memoria utilizada.
  tsp(ciudades, matrizCostos, salida);
  destruir_matriz(matrizCostos, ciudades->elems);
  destruir_ciudades(ciudades);
  return 0;
}