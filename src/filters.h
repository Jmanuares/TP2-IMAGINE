#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#include <atomic>


// SINGLE-THREAD FILTERS

void blackWhite(ppm& img);
void contrast(ppm& img, float contrast);
void brightness(ppm& img, float b);
void brightnessT(ppm& img, float brillo, unsigned int comienzoAltura, unsigned int finAltura);
void shades(ppm& img, unsigned char shades);
void merge(ppm& img1, ppm& img2, float alpha);
void frame(ppm& img, pixel color, int x);
void boxBlur(ppm &img);
void zoom(ppm &img, int n);
void edgeDetection(ppm &img, ppm &img_target);
void edgeDetectionT(ppm &img, ppm &img_target, int start, int finish);
void plain(ppm &img, unsigned char c);
void crop(ppm &img, unsigned char k, unsigned char t);
// MULTI-THREAD FILTERS

#endif