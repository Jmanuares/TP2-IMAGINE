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
	if (brillo >= 1 || brillo <= -1){
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
void brightnessT(ppm& img, float brillo, unsigned int comienzoAltura, unsigned int finAltura){
	pixel pixelUno;
	try
	{
		if (brillo > 1 || brillo < -1)
		{
			throw "El brillo debe estar entre -1 y 1";
		}

		for(unsigned int i = comienzoAltura; i < finAltura; i++)
		{
			for(unsigned int j = 0; j < img.width; j++)
			{
				pixelUno = img.getPixel(i, j);
				pixelUno.add(255 * brillo);
				img.setPixel(i,j, pixelUno.truncate());
				
			}
		}
	}
	catch(char error)
	{
		cout << error << endl;
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
};



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
void edgeDetectionT(ppm &img, ppm &img_target, int start, int finish){
	pixel p0,p1,p2,p3,p4,p5,p6,p7,p8,p9;
	pixel p_final;
	for (size_t i = start; i < finish - 1; i++)
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