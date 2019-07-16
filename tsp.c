#include "tsp.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARR 20
#define MAX_CAD 30

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

int buscar_index(Ciudades ciudades, char* nombre) {
  int index = 0;
  while (index < ciudades->elems &&
         strcmp(nombre, ciudades->nombres[index]) != 0) {
    index++;
  }
  return index;
}

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
  char c, cadena[30], c1[30], c2[30];
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