#include <my_struct.h>

void InitializeCircle(Shape *, double radius, double origin, double originY);
void InitializeRectangle(Shape *, double minX, double maxX, double minY, double maxY);
void InitializeTriangle(Shape *, double pt1X, double pt2X, double minY, double maxY);

double GetCircleArea(Shape *);
double GetRectangleArea(Shape *);
double GetTriangleArea(Shape *);

void GetCircleBoundingBox(Shape *, double *);
void GetRectangleBoundingBox(Shape *, double *);
void GetTriangleBoundingBox(Shape *, double *);