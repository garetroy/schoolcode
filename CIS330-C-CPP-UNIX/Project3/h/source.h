#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

class Source{
	public:
		Source(){updated = false; UpdateSource();};
		Image* GetOutput(){return &imageout;};
		virtual void Update();
		void UpdateSource(){imageout.SetSource(this);};
		virtual const char *SourceName() = 0;
		void UpdateBool(){updated = true;};
		bool IsUpdated(){return updated;};
	protected:
		Image imageout;
		virtual void Execute() = 0;
	private:
		bool updated; 
};

#endif