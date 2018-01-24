#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"
class Source{
	public:
		Image* GetOutput(){return &imageout;};
		virtual void Execute() = 0;
	protected:
		Image imageout;
	private:
};

#endif