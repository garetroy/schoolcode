#include "image.h"
#include "source.h"
void
Image::Update(){if(pixels == NULL){source->Update();};};