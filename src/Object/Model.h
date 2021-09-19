#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "../Core/Types.h"
#include "../Math/Matrix.h"

int InitModels(TScene* Scene);

void InitModel_all(TScene* Scene, TModel* Model, int mesh_type, int texture_type, float x, float y, float z, float xr, float yr, float zr, float xs, float ys, float zs);
#define InitModel(Scene, Model, mesh, texture,  x, y, z) InitModel_all(Scene, Model, mesh, texture, x, y, z, 0, 0, 0, 0, 0, 0)

// Draw Functions
void DrawModelScaled(TCore* Core, TModel* model, float x, float y, float z, float sx , float sy, float sz);
void DrawModelOffset(TCore* Core, TModel* model, float ox, float oy, float oz);
void DrawModelOffsetColor(TCore* Core, TModel* model, float ox, float oy, float oz, float r, float g, float b);
void DrawModel(TCore* Core, TModel* model);

#endif // MODEL_H_INCLUDED
