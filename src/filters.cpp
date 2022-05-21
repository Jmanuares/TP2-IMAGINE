#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>       /* sqrt */
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
	int r; 
	int g;
	int b;

	if (contrast >= 255 || contrast <= -255)
	{
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
	int r; 
	int g;
	int b;
	if (brillo >= 1 || brillo <= -1)
	{
		cout << "El brillo debe estar entre -1 y 1" << endl;
	}else{
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
	
}
void shades(ppm& img, unsigned char shades){
	int r; 
	int g;
	int b;
	int range = (int)(255/(int(shades)-1));
	int ge;
	int gris;
	
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



void zoom(ppm &img, ppm &img_zoomed, int n);
void edgeDetection(ppm &img, ppm &img_target);
