#include "image.h"
#include "source.h"
void
Image::Update() const {if(pixels == NULL){source->Update();};};