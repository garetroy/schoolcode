#include <stdio.h>
#include <stdlib.h>
#include "PNMreader.h"

void
PNMreader::Execute(){   
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL){
        char msg[1024];
        sprintf(msg, "%s: File could not be opened with filename:%s",SourceName(),filename);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    
    char magicNum[3] = {0};
    int width=0, height=0, maxVal=0;
    fscanf(fp, "%s\n%d %d\n%d\n", magicNum, &width,&height,&maxVal);
    if (width <= 0 || height <= 0 || maxVal <=0){
        char msg[1024];
        sprintf(msg, "%s: Width:%d, Height:%d, or maxVal:%d are set to a size <= 0", SourceName(), width, height, maxVal);
        DataFlowException e(SourceName(), msg);
        throw e; 
    }
    if (magicNum[0] == 0){
        char msg[1024];
        sprintf(msg, "%s: magicNum is NULL", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e; 
    }
    imageout.SetSize(height, width);
    imageout.SetMaxVal(maxVal);
    imageout.SetMagicNum(magicNum);
    Pixel *pixels=new Pixel[height*width];
    fread(pixels,sizeof(Pixel),width*height,fp);
    if (pixels == NULL){
        char msg[1024];
        sprintf(msg, "%s: Pixels are set to NULL", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e; 
    }
    imageout.SetPixels(pixels);
    try{
        fclose(fp);
    } catch(FILE fp){
        char msg[1024];
        sprintf(msg, "%s: File did not successfully close", SourceName());
    }

}