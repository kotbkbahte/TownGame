#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "../Core/Types.h"
#include "../Math/Matrix.h"


void obj2d_InitObj(TObject* obj, float x, float y, float r, float g, float b);

void obj2d_CreateRect(TObject* obj, float ox, float oy, float h, float w);

void DrawObject(TCore* Core, TObject* obj);

#endif // OBJECT_H_INCLUDED
