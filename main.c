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
    // printf("Entre al if\n");
    if (matriz[0][posActual] > 0) {
      //*(costoParcial) += matriz[0][posActual];
      if ((*(costoParcial) + matriz[0][posActual] < *(costoMejor) ||
           *(costoMejor) == 0)) {
        // printf("Encontre solucion\n");
        for (int i = 0; i < cantCiudades; i++) {
          mejorSol[i] = solParcial[i];
        }
        mejorSol[nivel] = mejorSol[0];
        *(costoMejor) = *(costoParcial) + matriz[0][posActual];
        //*(costoMejor) += matriz[0][posActual];
      }
      //*(costoParcial) -= matriz[0][posActual];
    }
  }

  else {
    // printf("Entre al else\n");
    for (int i = 0; i < cantCiudades; i++) {
      // printf("entre al for\n");
      if (*(costoParcial) < *(costoMejor) || *(costoMejor) == 0) {
        if (visitados[i] == 0 && matriz[posActual][i] > 0) {
          // printf("Encontre nodo\n");
          visitados[i] = 1;
          solParcial[nivel] = i;
          *(costoParcial) += matriz[posActual][i];
          resolver_tsp(matriz, visitados, solParcial, mejorSol, costoMejor,
                       costoParcial, nivel + 1, cantCiudades, i);
          visitados[i] = 0;
          // solParcial[nivel - 1] = i;
          *(costoParcial) -= matriz[posActual][i];
        }
      }
    }
  }
}

void tsp(Ciudades listaCiudades, int** matrizCostos, char* archivoSalida) {
  // printf("%d\n", listaCiudades->elems);
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
  int *costoMejor, *costoParcial;
  int cm = 0, cp = 0;
  costoMejor = &cm;
  costoParcial = &cp;
  // Agrego el ínidce de la primer ciudad y la marco como visitada.
  visitados[0] = 1;
  solParcial[0] = 0;
  resolver_tsp(matrizCostos, visitados, solParcial, mejorSol, costoMejor,
               costoParcial, 1, listaCiudades->elems, 0);
  escribir_solucion(archivoSalida, mejorSol, listaCiudades, matrizCostos,
                    *(costoMejor));
  printf("Archivo de salida generado.\n");
  // for (int k = 0; k < listaCiudades->elems + 1; k++) {
  //   printf("%d ", mejorSol[k]);
  // }
  // printf("\n%d\n", *(costoMejor));
}

int main() {
  Ciudades ciudades = crear_ciudades();
  int** matrizCostos;  // PEDIR NOMBRE ENTRADA POR TECLADO.
  char entrada[30], salida[30];
  printf("Ingrese el nombre del archivo de entrada:\n");
  scanf("%s", entrada);
  strcat(entrada, ".txt");
  printf("Ingrese el nombre del archivo de salida:\n");
  scanf("%s", salida);
  strcat(salida, ".txt");
  matrizCostos = leer_entrada(entrada, ciudades);
  // printf("%d\n", ciudades->elems);
  // imprimir_ciudades(ciudades);
  // imprimir_matriz(matrizCostos, ciudades->elems);
  tsp(ciudades, matrizCostos, salida);
  destruir_matriz(matrizCostos, ciudades->elems);
  destruir_ciudades(ciudades);
  return 0;
}