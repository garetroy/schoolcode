#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"

class Source{
	public:
		Source(){UpdateSource();};
		Image* GetOutput(){return &imageout;};
		virtual void Update(){Execute();};
		void UpdateSource(){imageout.SetSource(this);};
	protected:
		Image imageout;
		virtual void Execute() = 0;
	private:
};

#endif