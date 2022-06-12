#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;



// Ejercicio 0 (*)
// Dado un vector v, devuelve el valor maximo encontrado.
// NOTA: Se puede hacer en una línea
int mayor(const vector<int>& v);

// Ejercicio 1 (*)
// Dado un vector v, devuelve el reverso.
// NOTA: Se puede hacer en una linea
vector<int> reverso(const vector<int>& v);

// Ejercicio 2
// Dado un vector v y un entero k, rotar k posiciones los elementos de v.
// [1,2,3,4,5,6] rotado 2, deberia dar [3,4,5,6,1,2].
vector<int> rotar(const vector<int>& v, int k);

// Ejercicio 3 (*)
// Dado un vector v, hacer una función que lo modifique sumandole uno a todos sus elementos
// Determinar la cabecera de la funcion!!

// Ejercicio 4
// Dado un vector v de int, dice si esta ordenado(ya sea creciente o decrecientemente)
bool estaOrdenado(const vector<int>& v);

//Ejercicio 5 (*)
void mostrarVector(const vector<int>& v, ostream& out);
// Dado un vector de enteros muestra por la salida especificada en out, el vector
// Ejemplo: si el vector es <1, 2, 5, 65> se debe mostrar en la salida [1, 2, 5, 65]


//Ejercicio 6 (*)
void guardarVector(const vector<int>& v, string nombreArchivo);
// Dado un vector de enteros y el nombre de un archivo de salida,
// escribe al vector en el archivo. Ejemplo: si el vector es <1, 2, 5, 65>
// el archivo contiene [1, 2, 5, 65]
// NOTA:Reutilizar el ejercicio anterior!


//Ejercicio 7 
void cantidadApariciones(string nombreArchivo,string nombreArchivoOut,int max);
// Dado un archivo que contiene una lista de números, cuenta la cantidad de
// apariciones de cada uno y escribe el archivo nombreArchivoOut con una linea por cada
// numero encontrado, un espacio y la cantidad de apariciones
// El parametro max indica el número más grande que puede aparecer en el archivo
// Ejemplo: si el 1 aparece 44 veces, el 2 20 veces y no aparece ningun otro numer, 
// en la salida deberia haber dos lineas, la primera con "1 44" y la segunda "2 20". En este caso
// el parámetro max debería ser 2.



//Ejercicio 8 (opcional)
void palindromos(string nombreArchivo, string nombreArchivoOut);
// Dado el nombre de un archivo, lo filtra y devuelve los palindromos en el archivo salida, uno por linea.
