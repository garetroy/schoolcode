#include <stdio.h>
#include <stdlib.h>
#include "PNMreader.h"

void
PNMreader::Execute(){   
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL){
        printf("File Pointer is NULL");
    }
    char magicNum[3];
    int width, height, maxVal;
    fscanf(fp, "%s\n%d %d\n%d\n", magicNum, &width,&height,&maxVal);
    imageout.SetSize(height, width);
    imageout.SetMaxVal(maxVal);
    imageout.SetMagicNum(magicNum);
    Pixel *pixels=imageout.GetPixels();
    fread(pixels,sizeof(Pixel),width*height,fp);
    imageout.SetPixels(pixels);
    fclose(fp);
}