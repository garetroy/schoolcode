#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
		unsigned char red,green,blue;
} Pixel;

typedef struct{
	char magicNum[2];
	int maxval,height,width;
	Pixel *pixels;
} Image;

Image *ReadImage(char *filename){	
	FILE *fp;
	fp = fopen(filename, "r");
	fscanf(fp, "%s\n%d %d\n%d\n", image->magicNum,&image->width,&image->height,&image->maxval);
	image->pixels = (Pixel*)malloc(image->width * image->height * sizeof(Pixel));
	fread(image->pixels,sizeof(Pixel),image->width*image->height,fp);
	if (image->pixels == NULL){
		printf("Pixels ptr is Null");
	}
	fclose(fp);
	return image;
}


void WriteImage(Image *image, char *filename){
	FILE *fp;
	fp = fopen(filename, "w");
	fprintf(fp, "%s\n%d %d\n%d\n",image->magicNum,image->width,image->height,image->maxval);
	fwrite(image->pixels,3*image->width,image->height,fp);
	fclose(fp);
}


Image *YellowDiagonal(Image *image){
	int i,min;
	max = image->width * image->height /* This is the tops */
	for(i=0;i<max;i++){ /*This is checking to see if i is < max, which if it goes off graph, will not work*/
		image->pixels[i].red = 255;
		image->pixels[i].green = 255;
		image->pixels[i].blue = 0;
		i += image->width
	}
	return image;
}

int main(int argc, char *argv[]){
	Image *image;
	image = ReadImage(argv[1]);
	YellowDiagonal(image);
	WriteImage(image,argv[2]);
	free(image);
	return 0;
}