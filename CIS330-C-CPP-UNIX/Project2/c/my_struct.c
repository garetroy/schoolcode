/* This file should contain the 9 functions defined in prototypes.h */
#include <prototypes.h>

void InitializeCircle(Circle *C, double radius, double origin, double originY){
	C->radius = radius;
	C->origin = origin;
	C->originY = originY;
	return;
};

void InitializeRectangle(Rectangle *R, double minX, double maxX, double minY, double maxY){
	R->minX = minX;
	R->maxX = maxX;
	R->minY = minY;
	R->maxY = maxY;
	return;
};

void InitializeTriangle(Triangle *T, double pt1X, double pt2X, double minY, double maxY){
	T->pt1X = pt1X;
	T->pt2X = pt2X;
	T->minY = minY;
	T->maxY = maxY;
	return;
};

double GetCircleArea(Circle *C){
	return 3.14159*C->radius*C->radius;
};

double GetRectangleArea(Rectangle *R){
	return (R->maxX-R->minX)*(R->maxY-R->minY);
};

double GetTriangleArea(Triangle *T){
	return (T->pt2X-T->pt1X)*(T->maxY-T->minY)/2;
};

void GetCircleBoundingBox(Circle *C, double *bbox){
	bbox[0] = C->origin-C->radius;
	bbox[1] = C->origin+C->radius;
	bbox[2] = C->originY-C->radius;
	bbox[3] = C->originY+C->radius;
	return;
};

void GetRectangleBoundingBox(Rectangle *R, double *bbox){
	bbox[0] = R->minX;
	bbox[1] = R->maxX;
	bbox[2] = R->minY;
	bbox[3] = R->maxY;
	return;
};

void GetTriangleBoundingBox(Triangle *T, double *bbox){
	bbox[0] = T->pt1X;
	bbox[1] = T->pt2X;
	bbox[2] = T->minY;
	bbox[3] = T->maxY;
	return;
};
