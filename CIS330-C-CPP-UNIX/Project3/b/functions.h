#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <image.h>

void ReadImage(char *filename, Image &output);
void WriteImage(char *filename, Image &img);
void HalveInSize(Image &input, Image &output);
void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output);
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output);
void Blend(Image &input1, Image &input2, float factor, Image &output);
void ReadImage(char *filename, Image &image);
void WriteImage(char *filename, Image &image);

#endif