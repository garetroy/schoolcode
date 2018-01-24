#include "image.h"
#include "source.h"
void
Image::Update() const {
	if(pixels == NULL){
		if(source->IsUpdated()){
			;
		}else{
		source->UpdateBool();
		source->Update();
		};
	};
};