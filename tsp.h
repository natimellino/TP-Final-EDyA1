/* Estructura auxiliar para almacenar los nombres de las ciudades. El índice que
 * ocupa cada ciudad en el arreglo es el índice que representa a esa ciudad en
 * la matriz de costos. */

typedef struct _Ciudades {
  char** nombres;
  int elems;
} * Ciudades;

/* Devuelve un puntero del tipo Ciudades. */

Ciudades crear_ciudades();

/* Agrega una ciudad al arreglo de Ciudades. */

void agregar_ciudad(Ciudades ciudades, char* ciudad);

/* Imprime en pantalla los nombres de las ciudades. */

void imprimir_ciudades(Ciudades ciudades);

/* Busca en el arreglo de Ciduades una ciudad dada y devuelve su índice. Obs: la
 * función asume que la ciudad dada se encuentra en el arreglo. */

int buscar_index(Ciudades ciudades, char* nombre);

/* Dada una matriz, que representa la matriz de costos de las ciudades, la
 * imprime por pantalla. */

void imprimir_matriz(int** matriz, int elems);

/* Lee el archivo de entrada, guarda los nombres de las ciudades en el arreglo
 * de Ciudades, y devuelve una matriz de costos con los costos entre cada
 * ciudad. En la matriz cada índice representa la ciudad que esté almacenada en
 * el arreglo de Ciudades en dicho índice. */

int** leer_entrada(char* archivo, Ciudades ciudades);

/* Recibe una solución para el TSP en forma de arreglo de enteros, donde se
 * encuentra la secuencia de ciudades (representada por índices), y utilizando
 * los índices de la solución accede al arreglo de Ciudades y escribe la
 * secuencia de ciudades a visitar con sus costos.*/

void escribir_solucion(char* archivo, int solucion[], Ciudades ciudades,
                       int** matriz, int costoTotal);

/* Funciones de destrucción. */

void destruir_ciudades(Ciudades ciudades);

void destruir_matriz(int** matriz, int tam);