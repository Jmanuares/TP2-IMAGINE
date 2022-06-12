#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>      // std::ofstream
#define ONE_OVER_BILLION 1E-9


using namespace std;

// El siguiente es un template basico que pueden usar como base

int main(int argc , char* argv[]){
	
	// Asumimos que los filtros sin p1 se escriben primero (por lo tanto, el primer p1 es no nulo)
	// Asumimos que Zoom no se puede encadenar

	if(string(argv[1]) == "-help"){
		cout << "Uso: ./main <filtro> <nthreads> <[p1]> <img1> <custom_output> <[p2]> <img2>" << endl;
		return 0; 
	}
	else if(string(argv[1]) == "-filtros"){
		cout << """Los filtros que se pueden usar son plain, shades, brightness, contrast, edgeDetection, zoom, crop""" << endl;
		return 0; 
	}
	// Argumentos que hay que mandar a la hora de correr el programa
	string filter = string(argv[1]); // funcion del filtro
	unsigned int threads = atoi(argv[2]); // threads
	float p1 = atof(argv[3]); // variable
	float p2 = atof(argv[4]); // segunda variable
	string img1(argv[5]); // ruta a la img
	string out = string(argv[6]); // ruta para guardar img (out)
	
	
	ppm img(img1);
	
	cout << "Aplicando filtros"<< endl;
	struct timespec start, stop;    	
	clock_gettime(CLOCK_REALTIME, &start);

	if (filter == "plain")
		plain(img, (unsigned char)p1);
	else if (filter == "shades")
		shades(img, (unsigned char)p1);
	else if (filter == "brightness"){
		if (p1 > 1 || p1 < -1){
			cout << "El brillo debe estar entre -1 y 1" << endl;
		}else{
			if(threads==1){
				brightness(img, p1);
			}else{
				brightnessT(img, p1,threads);
			}
		}
	}
	else if (filter == "contrast")
		contrast(img, p1);
	else if (filter == "edgeDetection"){
		ppm img_target(img.width - 1, img.height - 1);
		if(threads==1){
			edgeDetection(img, img_target);
		}else{
			edgeDetectionT(img, img_target, threads);
		}
	}

	else if (filter == "zoom")
		zoom(img, (unsigned char)p1);
	else if (filter == "crop")
		crop(img, (unsigned char)p1,(unsigned char)p2);
	else
		cout << "No se selecciono filtro" << endl;
	
   	clock_gettime(CLOCK_REALTIME, &stop);

	double accum;
	accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION;
	printf("%lf s\n", accum);

	cout << "Escribiendo imagen" << endl;
	img.write(out);	
	file.open("../test/resultados.csv", ios::app);
	string outPrueba = to_string(imagen1.width) + "," + to_string(accum) + "," + to_string(threads) + "\n";
	cout << "Listo" << endl;
	file << outPrueba;
	file.close();

	return 0;
}