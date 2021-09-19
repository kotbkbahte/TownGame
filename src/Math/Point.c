#include "Point.h"

float math_distance2(TPoint2d* p1, TPoint2d* p2)
{
    return sqrt( math_sqr(p1->x - p2->x) + math_sqr(p1->y - p2->y) );
}

float math_distance3(TPoint3d* p1, TPoint3d* p2)
{
    return sqrt( math_sqr(p1->x - p2->x) +
                 math_sqr(p1->y - p2->y) +
                 math_sqr(p1->z - p2->z) );
}
