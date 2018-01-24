#ifndef PNM_READER
#define PNM_READER
#include "source.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
class PNMreader : public Source{
	public:
		PNMreader(char *filename_){strcpy(filename,filename_);}
		virtual void Execute();
	private:
		char filename[256];
};
#endif