#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARR 20

typedef struct _Ciudades {
  char** nombres;
  int elems;
} * Ciudades;

Ciudades crear_ciudades() {
  Ciudades nuevo = malloc(sizeof(struct _Ciudades));
  nuevo->nombres = malloc(sizeof(char*) * MAX_ARR);
  nuevo->elems = 0;
  return nuevo;
}

void agregar_ciudad(Ciudades ciudades, char* ciudad) {
  ciudades->nombres[ciudades->elems] = malloc(sizeof(char) * strlen(ciudad));
  strcpy(ciudades->nombres[ciudades->elems], ciudad);
  ciudades->elems++;
}

void imprimir_ciudades(Ciudades ciudades) {
  for (int i = 0; i < ciudades->elems; i++) {
    printf("%s\n", ciudades->nombres[i]);
  }
}

void imprimir_matriz(int** matriz, int elems) {
  for (int i = 0; i < elems; i++) {
    for (int j = 0; j < elems; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

int buscar_index(Ciudades ciudades, char* nombre) {
  int index = 0;
  while (index < ciudades->elems &&
         strcmp(nombre, ciudades->nombres[index]) != 0) {
    index++;
  }
  return index;
}

int** leer_entrada(char* archivo, Ciudades ciudades) {
  FILE* fp = fopen(archivo, "r");
  assert(fp != NULL);
  char c, cadena[30], c1[30], c2[30], cad[100];
  // char* token;
  int linea = 1, i = 0, nroCiudad = 0, costo, index1, index2;

  // Guardo los nombres de las ciudades.
  while (linea <= 3) {
    c = fgetc(fp);
    if (linea == 2 && c != ' ') {
      if (!isalpha(c)) {
        cadena[i] = '\0';
        agregar_ciudad(ciudades, cadena);
        nroCiudad++;
        i = 0;
      } else {
        cadena[i] = c;
        i++;
      }
    }
    if (c == '\n') linea++;
  }
  int cantCiudades = ciudades->elems;
  // imprimir_ciudades(ciudades);
  int** matrizCostos = malloc(sizeof(int*) * cantCiudades);
  for (int i = 0; i < cantCiudades; i++) {
    matrizCostos[i] = malloc(sizeof(int) * cantCiudades);
    for (int j = 0; j < cantCiudades; j++) {
      matrizCostos[i][j] = -1;
    }
  }
  while (fscanf(fp, "%[^,],%[^,],%d\n", c1, c2, &costo) != EOF) {
    char p1[30], p2[30];
    strcpy(p1, c1);
    strcpy(p2, c2);
    // printf("%s %s %d\n", p1, p2, costo);  // POSIBLE SALTO DE LINEA
    index1 = buscar_index(ciudades, p1);
    index2 = buscar_index(ciudades, p2);
    // printf("%d %d\n", index1, index2);
    matrizCostos[index1][index2] = costo;
    matrizCostos[index2][index1] = costo;
  }
  return matrizCostos;
  fclose(fp);
}

void escribir_solucion(char* archivo, int solucion[], Ciudades ciudades,
                       int** matriz, int costoTotal) {
  FILE* fp = fopen(archivo, "w+");
  int costo;
  for (int i = 0; i < ciudades->elems; i++) {
    costo = matriz[solucion[i]][solucion[i + 1]];
    fprintf(fp, "%s,%s,%d\n", ciudades->nombres[solucion[i]],
            ciudades->nombres[solucion[i + 1]], costo);
  }
  fprintf(fp, "Costo total: %d\n", costoTotal);
  fclose(fp);
}

void resolver_tsp(int** matriz, int visitados[], int solParcial[],
                  int mejorSol[], int* costoMejor, int* costoParcial, int nivel,
                  int cantCiudades, int posActual) {
  if (nivel == cantCiudades) {
    // printf("Entre al if\n");
    if (matriz[0][posActual] > 0 &&
        (*(costoParcial) < *(costoMejor) || *(costoMejor) == 0)) {
      // printf("Encontre solucion\n");
      for (int i = 0; i < cantCiudades; i++) {
        mejorSol[i] = solParcial[i];
        *(costoMejor) = *(costoParcial);
      }
      mejorSol[nivel] = mejorSol[0];
      *(costoMejor) += matriz[0][posActual];
    }
  }

  else {
    // printf("Entre al else\n");
    for (int i = 0; i < cantCiudades; i++) {
      // printf("entre al for\n");
      if (visitados[i] == 0 && matriz[posActual][i] > 0) {
        // printf("Encontre nodo\n");
        visitados[i] = 1;
        solParcial[nivel] = i;
        *(costoParcial) += matriz[posActual][i];
        if (*(costoParcial) < *(costoMejor) || *(costoMejor) == 0) {
          resolver_tsp(matriz, visitados, solParcial, mejorSol, costoMejor,
                       costoParcial, nivel + 1, cantCiudades, i);
        }
        visitados[i] = 0;
        // solParcial[nivel - 1] = i;
        *(costoParcial) -= matriz[posActual][i];
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
  return 0;
}