#ifndef COLOR_H
#define COLOR_H
#include "source.h"
class Color: public Source{
	private:
		int h,w;
		unsigned char r,g,b;
	public:
		Color(int _w, int _h, unsigned char _r, unsigned char _g, unsigned char _b){h=_h;w=_w;r=_r;g=_g;b=_b;};
		virtual const char *SourceName(){return "Color";};
		virtual void Execute();
};
#endif