#include <functions.h>
#include <stdlib.h>
#include <stdio.h>

void HalveInSize(Image &image1, Image &image2){
	image2 = Image(image1.height/2,image1.width/2);
	if(image2.pixels == NULL){
			printf("output pointers allocated as NULL");
	}
    int width_adjustment = 4*image2.width;
    for(int i=0;i<image2.height;i++){
    	for(int j=0;j<image1.height;j++){
    		image2.pixels[i*image2.width+j] = image1.pixels[i*width_adjustment+2*j];
    	}
    }
}

void LeftRightConcatenate(Image &leftInput, Image &rightInput, Image &output){
		output = Image(leftInput.height,leftInput.width + rightInput.width);
		if(output.pixels == NULL){
			printf("output pointers allocated as NULL");
		}
		for(int i=0; i<output.height;i++){
			for(int j=0; j<output.width; j++){
				if(j > leftInput.width){
					output.pixels[i*output.width+j] = rightInput.pixels[i*rightInput.width+j];	
				} else {
					output.pixels[i*output.width+j] = leftInput.pixels[i*leftInput.width+j];
				}
			}
		}
}

void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
		output = Image(bottomInput.height + topInput.height,topInput.width);
		if(output.pixels == NULL){
			printf("output pointers allocated as NULL");
		}
		for(int i=0; i<output.height;i++){
			for(int j=0; j<output.width; j++){
				if(i < topInput.height){
					output.pixels[i*output.width+j] = topInput.pixels[i*output.width+j];	
				} else {
					output.pixels[i*output.width+j] = bottomInput.pixels[(i-topInput.height)*output.width+j];
				}
			}
		}
    }

void Blend(Image &input, Image &input1, float factor, Image &output){
		float otherFactor = 1 - factor;
		output = Image(input.height, input.width);
		if(output.pixels == NULL){
			printf("output pointers allocated as NULL");
		}
		for(int i=0; i<input.height;i++){
			for(int j=0; j<input1.width; j++){
				output.pixels[i*output.width+j].blue = (unsigned char)((input1.pixels[i*input1.width+j].blue*otherFactor) + (factor * input.pixels[i*input.width+j].blue));
				output.pixels[i*output.width+j].green = (unsigned char)((input1.pixels[i*input1.width+j].green*otherFactor) + (factor * input.pixels[i*input.width+j].green));
				output.pixels[i*output.width+j].red = (unsigned char)((input1.pixels[i*input1.width+j].red*otherFactor) + (factor * input.pixels[i*input.width+j].red));

			}
		}
    }
