#ifndef PNM_WRITER
#define PNM_WRITER
#include "sink.h"
#include <fstream>
#include <iostream>
class PNMwriter : public Sink{
	public:
		void Write(char *filename_);
	private:
};

#endif