typedef struct{
	double minX;
	double minY;
	double maxX;
	double maxY;
}Rectangle;

typedef struct{
	double origin;
	double originY;
	double radius;
}Circle;

typedef struct{
	double pt1X;
	double pt2X;
	double minY;
	double maxY;
}Triangle;

typedef union{
	Circle c;
	Rectangle r;
	Triangle t; 
}ShapeUnion;

typedef struct{
	double (*GetArea)();
	void (*GetBoundingBox)();
}FunctionTable;

typedef enum{
	circle,
	rectangle,
	triangle
}ShapeType;

typedef struct{
	ShapeUnion su;
	ShapeType st;
	FunctionTable ft;
}Shape;