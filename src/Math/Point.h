#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <math.h>

#define math_sqr(a) (a) * (a)


typedef struct
{
    float x, y;
} TPoint2d;

typedef struct
{
    int x, y;
} TPoint2d_i;

typedef struct
{
    float x, y, z;
} TPoint3d;

typedef struct
{
    TPoint3d m_Position;
    TPoint3d m_Normal;
    TPoint2d m_TexCoord;
    TPoint3d m_Color;
}  TVertex;

typedef struct
{
    TPoint3d m_Position;
    TPoint2d m_TexCoord;
} TVertex_pt;



#endif // POINT_H_INCLUDED
