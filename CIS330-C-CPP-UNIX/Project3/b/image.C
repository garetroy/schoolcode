#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

void ReadImage(char *filename, Image &image){   
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("File Pointer is NULL");
    }
    fscanf(fp, "%s\n%d %d\n%d\n", image.magicNum,&image.width,&image.height,&image.maxVal);
    image = Image(image.height, image.width);
    fread(image.pixels,sizeof(Pixel),image.width*image.height,fp);
    fclose(fp);
}

void WriteImage(char *filename, Image &image){
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL){
        printf("File Pointer is NULL");
    }
    fprintf(fp, "%s\n%d %d\n%d\n",image.magicNum,image.width,image.height,image.maxVal);
    fwrite(image.pixels,sizeof(Pixel),image.width*image.height,fp);
    fclose(fp);
}

