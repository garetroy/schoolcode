/* This file should contain the 9 functions defined in prototypes.h */
#include <prototypes.h>

void InitializeCircle(Shape *C, double radius, double origin, double originY){
	C->su.c.radius = radius;
	C->su.c.origin = origin;
	C->su.c.originY = originY;
	C->ft.GetArea = &GetCircleArea;
	C->ft.GetBoundingBox = &GetCircleBoundingBox;
	return;
};

void InitializeRectangle(Shape *R, double minX, double maxX, double minY, double maxY){
	R->su.r.minX = minX;
	R->su.r.maxX = maxX;
	R->su.r.minY = minY;
	R->su.r.maxY = maxY;
	R->ft.GetArea = &GetRectangleArea;
	R->ft.GetBoundingBox = &GetRectangleBoundingBox;
	return;
};

void InitializeTriangle(Shape *T, double pt1X, double pt2X, double minY, double maxY){
	T->su.t.pt1X = pt1X;
	T->su.t.pt2X = pt2X;
	T->su.t.minY = minY;
	T->su.t.maxY = maxY;
	T->ft.GetArea = &GetTriangleArea;
	T->ft.GetBoundingBox = &GetTriangleBoundingBox;
	return;
};

double GetCircleArea(Shape *C){
	return 3.14159*C->su.c.radius*C->su.c.radius;
};

double GetRectangleArea(Shape *R){
	return (R->su.r.maxX-R->su.r.minX)*(R->su.r.maxY-R->su.r.minY);
};

double GetTriangleArea(Shape *T){
	return (T->su.t.pt2X-T->su.t.pt1X)*(T->su.t.maxY-T->su.t.minY)/2;
};

void GetCircleBoundingBox(Shape *C, double *bbox){
	bbox[0] = C->su.c.origin-C->su.c.radius;
	bbox[1] = C->su.c.origin+C->su.c.radius;
	bbox[2] = C->su.c.originY-C->su.c.radius;
	bbox[3] = C->su.c.originY+C->su.c.radius;
	return;
};

void GetRectangleBoundingBox(Shape *R, double *bbox){
	bbox[0] = R->su.r.minX;
	bbox[1] = R->su.r.maxX;
	bbox[2] = R->su.r.minY;
	bbox[3] = R->su.r.maxY;
	return;
};

void GetTriangleBoundingBox(Shape *T, double *bbox){
	bbox[0] = T->su.t.pt1X;
	bbox[1] = T->su.t.pt2X;
	bbox[2] = T->su.t.minY;
	bbox[3] = T->su.t.maxY;
	return;
};
