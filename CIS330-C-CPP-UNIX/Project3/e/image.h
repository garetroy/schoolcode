#ifndef IMAGE_H
#define IMAGE_H
#include <string.h>
#include <stdlib.h>

class Source;

class Pixel{
		public:
			unsigned char red,green,blue;
};

class Image{
	public:
		Image(void){strcpy(magicNum,"P6");maxVal=255; height=100; width=100;pixels=new Pixel[height*width];};
		Image(int h, int w){strcpy(magicNum, "P6");maxVal=255;height=h;width=w;pixels=new Pixel[height*width];};
		~Image(){delete [] pixels;};
		Image(const Image &i){strcpy(magicNum,i.magicNum); maxVal = i.maxVal; height = i.height; width = i.width;};
		void SetSize(int h, int w){height = h; width = w;delete [] pixels;pixels=new Pixel[height*width];};
		int GetHeight(){return height;};
		int GetWidth(){return width;};
		char* GetMagicNum(){return magicNum;};
		int GetMaxVal(){return maxVal;};
		void SetMaxVal(int maxVal_){maxVal = maxVal_;};
		void SetMagicNum(char* magicNum_){strcpy(magicNum,magicNum_);};
		void SetPixels(Pixel* pixels_){pixels = pixels_;};
		void SetPixel(int h, int w, Pixel p){pixels[h*width+w] = p;};
		Pixel GetPixel(int h, int w){return pixels[h*width+w];}
		Pixel* GetPixels(){return pixels;};
		void Update();
		void SetSource(Source *_source){source = _source;};
	private:
		Pixel *pixels;
		char magicNum[3];
		int maxVal,height,width;
		Source *source;
};

#endif