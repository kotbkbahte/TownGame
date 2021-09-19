#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "../Core/Types.h"
#include "ObjLoader.h"
#include "../Math/Matrix.h"

int InitMeshes(TScene* Scene);
void DrawMesh(TCore* Core, TMesh* mesh);

int LoadMeshFromObj(TMesh* Mesh, const char* file_name);


void CreateSimpleMesh(TSimpleMesh* Mesh, int vert_count, int vert_size , float* vertices, GLenum usage);


void CreateMesh(TMesh* mesh,
                unsigned int* indices, int indices_count,
                TVertex* vertices, int vertices_count);
void SetupMesh_pnt(TMesh* mesh);
void SetupSimpleMesh(TSimpleMesh* Mesh, GLenum usage);



#endif // MESH_H_INCLUDED
