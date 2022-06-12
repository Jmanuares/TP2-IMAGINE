#include "taller.h"

// ACLARACION: Todas las funciones devuelven algo del tipo necesario, esto es 
// para que no explote cuando vayan compilando (y de paso para que no se olviden
//de devolver el tipo correcto)

// En algunos casos hay funciones de stl de c++ que ya resuelven cada ejercicio.
// Obviamente no vale utilizarlas para resolver

// En algunos casos es posible usar objetos iteradores que simplifican algunas
// operaciones. Es posible utilizarlos pero consultenme para chequear 

int mayor(const vector<int>& v)
{
	int mayor = 0;
	for (int i = 0 ; i < v.size(); i++){
		if (v[i] > mayor){
			mayor = v[i];	
		}	
	}
	return mayor;
}

// Ejercicio 1 
// Dado un vector v, devuelve el reverso.
// Se puede hacer en una línea usando iteradores (en este caso no vale usarlos)

vector<int> reverso(const vector<int>& v)
{
	vector<int> reverso(v.size()-1);
	int aux = 0;

	for (int i = v.size()-1; i >= 0; i--)
	{
		reverso[aux] = v[i];
		aux++;	
	}
	return reverso;
}

// Ejercicio 2
// Dado un vector v y un entero k, rotar k posiciones los elementos de v.
// [1,2,3,4,5,6] rotado 2, deberia dar [3,4,5,6,1,2].
vector<int> rotar(const vector<int>& v, int k){
	vector<int> rotada(v.size());
	for (int i = 0; i < v.size(); i++){
		rotada[i] = v[i];
		
	}
	for (int j = 0; j < k; j++){
		rotada.push_back(v[j]);
		rotada.erase(rotada.begin());
	}
	return rotada;
}

// Ejercicio 3
// Dado un vector v, hacer una función que lo modifique sumandole uno a todos 
// sus elementos. RECORDAR determinar la cabecera de la funcion y definir
// la misma en  taller.h !!

void sumar(vector<int>& v){
	for (int i : v){
		v[i] = v[i] + 1;
	}
}

// Ejercicio 4
// Dado un vector, dice si esta ordenado crecientemente o decrecientemente
bool estaOrdenado(const vector<int>& v){
	int aux = 0;
	bool aux;

	for(int i = 0; i < v.size(); i++){
		aux = v[i];
		for (int j = i+1; j < v.size(); j++){
			if (aux >= v[j]){
				return false;
			}
			else{
				aux = true;
			}	
		}
	}	
	if (aux == true)return true;
	return false;
}

// Ejercicio 5
// Dado un vector de enteros, lo muestra por la salida estándar (consola)
// Ej: si el vector es <1, 2, 5, 65> se debe mostrar en pantalla [1, 2, 5, 65]

// HINT: Esta función es general, out es del tipo de dato ostream. 
// Eso significa que el parametro out puede ser cou o bien podrías ser un 
// archivo de texto instancia de ofstream (que hereda de ostream).
// En cualquier caso puedo usar el operador << para escribir.

void mostrarVector(const vector<int>& v, ostream& out){
	string str = "";
	
	for (int i : v){
		str.append(to_string(i));
		str.append(", ");
	}
	str = str.substr(0, str.length() - 2);

	out << str << endl;

	return;
}


// Ejercicio 6 
// Dado un vector de enteros y el nombre de un archivo de salida,
// escribe al vector en el archivo. Ejemplo: si el vector es <1, 2, 5, 65>
// el archivo contiene [1, 2, 5, 65]
// Ojo con el constructor de ofstream. 
// Es importante hacer la conversion del string a char* usando c_str().
// HINT: Reutilizar la función anterior!

void guardarVector(const vector<int>& v, string nombreArchivo){
	string str = "";
	
	for (int i : v)
	{
		str.append(to_string(i));
		str.append(", ");
	}

	str = str.substr(0, str.length() - 2);

   	ofstream file(nombreArchivo.c_str()); 
   	if(file.is_open())
   	{
		file << str;   	
		file.close();
		
   	}
   	return;
}


//Ejercicio 7 
// Dado un archivo que contiene una lista de números, contar la cantidad de
// apariciones de cada uno y escribir nombreArchivoOut con una linea por cada
// numero encontrado, un espacio y la cantidad de apariciones.
// El parametro max indica el número más grande que puede aparecer en el archivo
// Ejemplo: si el 1 aparece 44 veces y el 2 20 veces (y no hay otros nums)
// en la salida deberia haber dos lineas, "1 44" y la segunda "2 20"

void cantidadApariciones(string nombreArchivo, string nombreArchivoOut,int max){
	ifstream fileIn(nombreArchivo.c_str());
	string line;
	vector<int> nums(10, 0);
	while (getline(fileIn, line)) {

		for (int ch2 = 0; ch2 < max; ch2++){
			size_t count = 0;

			for (char i : line){
				std::string tmp = std::to_string(ch2);
    			char const *ch = tmp.c_str();
				if (i == *ch){
					count++;
				}
			}
			nums[ch2] = nums[ch2] + count;
			
		}
    }
    ofstream fileOut(nombreArchivoOut.c_str());
	for(int i = 0; i< nums.size();i++){
		if (nums[i] != 0){
			fileOut << i;
			fileOut << " ";
			fileOut << nums[i];
			fileOut<< "\n";
		}
	}

	return;
} 

