#include <stdio.h>
#include <stdlib.h>
#include "PNMreader.h"

void
PNMreader::Execute(){
    FILE *fp;
    int error;
    fp = fopen(filename, "rb");
    if (fp == NULL){
        char msg[1024];
        sprintf(msg, "%s: file could not be opened with filename: %s Reason: %s",SourceName(),filename,strerror(errno));
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    char magicNum[3] = {0};
    int width=0, height=0, maxVal=0;
    error = fscanf(fp, "%s\n%d %d\n%d\n", magicNum, &width,&height,&maxVal);
    if (error < 0){
        char msg[1024];
        sprintf(msg, "%s: fscanf failed. Reason: %s",SourceName(),strerror(errno));
        DataFlowException e(SourceName(), msg);
        throw e;
    }
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
    Pixel *pixels= imageout.GetPixels();
    if (pixels == NULL){
        char msg[1024];
        sprintf(msg, "%s: failed to set pixels in preperation for fread",SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    error = fread(pixels,sizeof(Pixel),width*height,fp);
    if (error < 0){
        char msg[1024];
        sprintf(msg, "%s: failed to fread. Reason: %s",SourceName(),strerror(errno)); //perror returns specified string, then reason string for the errno
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (pixels == NULL){
        char msg[1024];
        sprintf(msg, "%s: pixels are set to NULL", SourceName());
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