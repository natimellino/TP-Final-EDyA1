#include "tsp.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARR 20
#define MAX_CAD 30

/* Funciones asociadas a la estructura Ciudades. */

Ciudades crear_ciudades() {
  Ciudades nuevo = malloc(sizeof(struct _Ciudades));
  nuevo->nombres = malloc(sizeof(char*) * MAX_ARR);
  nuevo->elems = 0;
  return nuevo;
}

void agregar_ciudad(Ciudades ciudades, char* ciudad) {
  ciudades->nombres[ciudades->elems] =
      malloc(sizeof(char) * (strlen(ciudad) + 1));
  strcpy(ciudades->nombres[ciudades->elems], ciudad);
  ciudades->elems++;
}

void imprimir_ciudades(Ciudades ciudades) {
  for (int i = 0; i < ciudades->elems; i++) {
    printf("%s\n", ciudades->nombres[i]);
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

/* Imprime una matriz de enteros. */

void imprimir_matriz(int** matriz, int elems) {
  for (int i = 0; i < elems; i++) {
    for (int j = 0; j < elems; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

/* Funciones de lectura y escritura de archivos. */

int** leer_entrada(char* archivo, Ciudades ciudades) {
  FILE* fp = fopen(archivo, "r");
  assert(fp != NULL);
  char c, cadena[MAX_CAD], c1[MAX_CAD], c2[MAX_CAD];
  ;
  int linea = 1, i = 0, costo, index1, index2, cantCiudades;

  // Guardo los nombres de las ciudades.
  while (linea <= 3) {
    c = fgetc(fp);
    if (linea == 2 && c != ' ') {
      if (!isalpha(c)) {
        cadena[i] = '\0';
        agregar_ciudad(ciudades, cadena);
        i = 0;
      } else {
        cadena[i] = c;
        i++;
      }
    }
    if (c == '\n') linea++;
  }
  cantCiudades = ciudades->elems;

  // Creo la matriz de costos.  //ENCAPSULAR EN UNA FUNCION.

  int** matrizCostos = malloc(sizeof(int*) * cantCiudades);
  for (int i = 0; i < cantCiudades; i++) {
    matrizCostos[i] = malloc(sizeof(int) * cantCiudades);
    for (int j = 0; j < cantCiudades; j++) {
      matrizCostos[i][j] = -1;
    }
  }

  // Almaceno en la matriz los costos de las ciudades.

  while (fscanf(fp, "%[^,],%[^,],%d\n", c1, c2, &costo) != EOF) {
    index1 = buscar_index(ciudades, c1);
    index2 = buscar_index(ciudades, c2);
    if (index1 < cantCiudades && index2 < cantCiudades) {
      matrizCostos[index1][index2] = costo;
      matrizCostos[index2][index1] = costo;
    }
  }
  fclose(fp);
  return matrizCostos;
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

/* Funciones de destrucción. */

void destruir_ciudades(Ciudades ciudades) {
  for (int i = 0; i < ciudades->elems; i++) {
    free(ciudades->nombres[i]);
  }
  free(ciudades->nombres);
  free(ciudades);
}

void destruir_matriz(int** matriz, int tam) {
  for (int i = 0; i < tam; i++) {
    free(matriz[i]);
  }
  free(matriz);
}