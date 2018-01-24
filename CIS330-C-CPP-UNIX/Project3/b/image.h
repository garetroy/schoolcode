#ifndef IMAGE_H
#define IMAGE_H
#include <string.h>
#include <stdlib.h>

struct Pixel{
		unsigned char red,green,blue;
};

struct Image{
	public:
		char magicNum[3];
		int maxVal,height,width;
		Pixel *pixels;
		Image(void){strcpy(magicNum,"P6");maxVal=255; height=100; width=100;};
		Image(int h, int w){height=h; width=w;maxVal=255;strcpy(magicNum, "P6");pixels=new Pixel[height*width];};
		Image(const Image &i){strcpy(magicNum,i.magicNum); maxVal = i.maxVal; height = i.height; width = i.width;};
		~Image(){delete [] pixels;};
		void Reset(int h, int w){height = h; width = w;};
};

#endif