#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>   
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  
#include <fstream>  

#define BLACK 0

using namespace std;


unsigned char truncate(float color)
{ 
    return (color > 255) ? 255 : ((color < 0) ? 0: (unsigned char)color); 
}

void plain(ppm& img, unsigned char c)
{

	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)			
			img.setPixel(i, j, pixel(c,c,c)); 

}


void contrast(ppm& img, float contrast){
	int r,g,b;

	if (contrast >= 255 || contrast <= -255){
		cout << "El contraste debe estar entre -255 y 255" << endl;
	}else{
		int f =	(int)((259*(contrast+255))/(255*(259-contrast)));
		for(int i = 0; i < img.height; i++){
			for(int j = 0; j < img.width; j++){		
				r = img.getPixel(i, j).r; 
				g = img.getPixel(i, j).g; 
				b = img.getPixel(i, j).b;	
				r = truncate(f*(r - 128) + 128);
				g = truncate(f*(g - 128) + 128); 
				b = truncate(f*(b - 128) + 128);

				img.setPixel(i, j, pixel(r,g,b));
			}
		}
	}
}

void brightness(ppm& img, float brillo){
	int r,g,b;
	for(int i = 0; i < img.height; i++){
		for(int j = 0; j < img.width; j++){		
			r = img.getPixel(i, j).r; 
			g = img.getPixel(i, j).g; 
			b = img.getPixel(i, j).b;
			r = truncate(r + 255*brillo);
			g = truncate(g + 255*brillo); 
			b = truncate(b + 255*brillo);

			img.setPixel(i, j, pixel(r,g,b));
		}
	}
}
//Filtro de brillo adaptado para threads
void brightnessParaThreads(ppm& img, float brillo, int strt, int fin){
	int r,g,b;
	for(strt; strt < fin; strt++){
		for(int j = 0; j < img.width; j++){		
			r = img.getPixel(strt, j).r; 
			g = img.getPixel(strt, j).g; 
			b = img.getPixel(strt, j).b;
			r = truncate(r + 255*brillo);
			g = truncate(g + 255*brillo); 
			b = truncate(b + 255*brillo);

			img.setPixel(strt, j, pixel(r,g,b));
		}
	}
}
//Divide en threads para llamar a el filtro brillo
void brightnessT(ppm& img, float brillo, int hilos){
	int limites = int(img.height / hilos),strt,fin;
	vector<thread> threads;
	for (int i = 0; i < hilos; i++)
	{
		strt = i * limites;
		fin = (i + 1) * limites;
		threads.push_back(thread(brightnessParaThreads, ref(img), brillo,strt,fin));
	}
	for (int i = 0; i < hilos; i++){
		threads[i].join();
	}
}


void shades(ppm& img, unsigned char shades){
	int r,g,b,ge,gris;
	int range = (int)(255/(int(shades)-1));
	
	for(int i = 0; i < img.height; i++){
		for(int j = 0; j < img.width; j++){		
			r = img.getPixel(i, j).r; 
			g = img.getPixel(i, j).g; 
			b = img.getPixel(i, j).b;
			ge = (int)((r+g+b)/3);

			gris = truncate((int)((ge/range)*range));
			img.setPixel(i, j, pixel(gris,gris,gris));
		}
	}
}



void zoom(ppm &img, int n){
	ppm img_zoomed(img.width * n, img.height * n);
	unsigned int posicionX,posicionY;
	for (int i = 0; i < img.height; i++)
		for (int j = 0; j < img.width; j++){
			pixel p = img.getPixel(i, j);

			posicionX = (j + (j * (n - 1)));
			posicionY = (i + (i * (n - 1)));

			for (int a = 0; a < n; a++)
				for (int b = 0; b < n; b++){
					img_zoomed.setPixel(posicionY + a, posicionX + b, p);
				}
		}
	
    img = img_zoomed;
}



void crop(ppm &img, unsigned char k, unsigned char t){
	ppm img_target = ppm(img.width - t, img.height - k);
	for (size_t i = k; i < img.height; i++)
	{
		for (size_t j = t; j < img.width; j++)
		{
			img_target.setPixel(i - k, j - t, img.getPixel(i, j));
		}
	}
	img = img_target;

};
	
void edgeDetection(ppm &img, ppm &img_target){
	pixel p0,p1,p2,p3,p4,p5,p6,p7,p8,p9;
	pixel p_final;
	
	for (size_t i = 1; i < img.height - 1; i++)
	{
		for (size_t j = 1; j < img.width - 1; j++)
		{
			p_final = pixel();
			p0 = img.getPixel(i - 1, j - 1);
			p1 = img.getPixel(i - 1, j);
			p2 = img.getPixel(i - 1, j + 1);
			p3 = img.getPixel(i, j - 1);
			p4 = img.getPixel(i, j);
			p5 = img.getPixel(i, j + 1);
			p6 = img.getPixel(i + 1, j - 1);
			p7 = img.getPixel(i + 1, j);
			p8 = img.getPixel(i + 1, j + 1);

			unsigned int gxr = (p0.r - p2.r + 2 * p3.r - 2 * p5.r + p6.r - p8.r);
			unsigned int gyr = (p0.r + 2 * p1.r + p2.r - p6.r - 2 * p7.r - p8.r);
			p_final.r = sqrt(gxr * gxr + gyr * gyr);
			
			unsigned int gxg = (p0.g - p2.g + 2 * p3.g - 2 * p5.g + p6.g - p8.g);
			unsigned int gyg = (p0.g + 2 * p1.g + p2.g - p6.g - 2 * p7.g - p8.g);
			p_final.g = sqrt(gxg * gxg + gyg * gyg);

			unsigned int gxb = (p0.b - p2.b + 2 * p3.b - 2 * p5.b + p6.b - p8.b);
			unsigned int gyb = (p0.b + 2 * p1.b + p2.b - p6.b - 2 * p7.b - p8.b);
			p_final.b = sqrt(gxb * gxb + gyb * gyb);

			p_final.truncate();
			img_target.setPixel(i - 1, j - 1, p_final);
		}
	}
    img = img_target;
}


void edgeDetectionParaThreadear(ppm img, ppm *img_target, int strt, int fin){
	for (size_t i = strt + 1; i < fin - 1; i++)
	{
		for (size_t j = 1; j < img.width - 1; j++)
		{
			pixel p_final = pixel();
			// movy, movx
			// ppmMutex.lock();			
			pixel p0 = img.getPixel(i - 1, j - 1);
			pixel p1 = img.getPixel(i - 1, j);
			pixel p2 = img.getPixel(i - 1, j + 1);
			pixel p3 = img.getPixel(i, j - 1);
			pixel p4 = img.getPixel(i, j);
			pixel p5 = img.getPixel(i, j + 1);
			pixel p6 = img.getPixel(i + 1, j - 1);
			pixel p7 = img.getPixel(i + 1, j);
			pixel p8 = img.getPixel(i + 1, j + 1);
			// ppmMutex.unlock();
			//p_final.r = (p0.r + p1.r + p2.r + p3.r + p4.r + p5.r + p6.r + p7.r + p8.r) / 9;
			//p_final.g = (p0.g + p1.g + p2.g + p3.g + p4.g + p5.g + p6.g + p7.g + p8.g) / 9;
			//p_final.b = (p0.b + p1.b + p2.b + p3.b + p4.b + p5.b + p6.b + p7.b + p8.b) / 9;
			unsigned int gxr = (p0.r - p2.r + 2 * p3.r - 2 * p5.r + p6.r - p8.r);
			unsigned int gyr = (p0.r + 2 * p1.r + p2.r - p6.r - 2 * p7.r - p8.r);
			p_final.r = sqrt(gxr * gxr + gyr * gyr);
			unsigned int gxg = (p0.g - p2.g + 2 * p3.g - 2 * p5.g + p6.g - p8.g);
			unsigned int gyg = (p0.g + 2 * p1.g + p2.g - p6.g - 2 * p7.g - p8.g);
			p_final.g = sqrt(gxg * gxg + gyg * gyg);
			unsigned int gxb = (p0.b - p2.b + 2 * p3.b - 2 * p5.b + p6.b - p8.b);
			unsigned int gyb = (p0.b + 2 * p1.b + p2.b - p6.b - 2 * p7.b - p8.b);
			p_final.b = sqrt(gxb * gxb + gyb * gyb);
			p_final.truncate();
			// ppmMutex.lock();
			img_target->setPixel(i - 1, j - 1, p_final);
			// ppmMutex.unlock();
		}
	}
}

void edgeDetectionT(ppm &img, ppm &img_target, int hilos){
	int limites = int(img.height / hilos),strt,fin;
	int offset = (img.height) - (limites * hilos);
	vector<thread> threads;
	for (int i = 0; i < hilos; i++)
	{
		strt = i * limites;
		fin = (i + 1) * limites;
		if (i == hilos - 1) {
			fin += offset;
		}
		threads.push_back(thread(edgeDetectionParaThreadear, img, &img_target, strt, fin));
	}
	for (int i = 0; i < hilos; i++){
		threads[i].join();
	}
	img = img_target;
}