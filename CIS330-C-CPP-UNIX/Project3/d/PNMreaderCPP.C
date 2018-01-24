#include "PNMreaderCPP.h"
using namespace std;
void
PNMreader::Execute(){
	char magicNum[3];
	int width, height, maxVal;
	ifstream infile;
	infile.open(filename);
	infile >> magicNum;
	infile >> width >> height;
	infile >> maxVal;
	imageout.SetSize(height,width);
	imageout.SetMagicNum(magicNum);
	imageout.SetMaxVal(maxVal);
	Pixel *pixels = new Pixel[height*width];
	infile.ignore(256, '\n');
	unsigned char pix[3];
    for (int i = 0; i < width * height; ++i) {
        infile.read(reinterpret_cast<char *>(pix), 3);
        pixels[i].red = pix[0];
		pixels[i].green = pix[1];
		pixels[i].blue = pix[2];
    }
	imageout.SetPixels(pixels);
	infile.close();
 }