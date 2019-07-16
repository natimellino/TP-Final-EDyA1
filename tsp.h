typedef struct _Ciudades {
  char** nombres;
  int elems;
} * Ciudades;

Ciudades crear_ciudades();

void agregar_ciudad(Ciudades ciudades, char* ciudad);

void imprimir_ciudades(Ciudades ciudades);

int buscar_index(Ciudades ciudades, char* nombre);

void imprimir_matriz(int** matriz, int elems);

int** leer_entrada(char* archivo, Ciudades ciudades);

void escribir_solucion(char* archivo, int solucion[], Ciudades ciudades,
                       int** matriz, int costoTotal);

void destruir_ciudades(Ciudades ciudades);

void destruir_matriz(int** matriz, int tam);