#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <SDL.h>
#include <glad/glad.h>
#include <stdio.h>

#define True 1
#define False 0

#define MAX_VERTEX_COUNT 100


#define random_color (float)rand()/(float)(RAND_MAX), (float)rand()/(float)(RAND_MAX), (float)rand()/(float)(RAND_MAX)
#define rgb_to_float(a, b, c) a/255.0f, b/255.0f, c/255.0f


#include "../Math/Point.h"
#include "../Math/Vector.h"


typedef struct
{
    float r, g, b;
} TColor;

typedef struct
{
    TVertex* m_Vertices;
    int m_VerticesCount;

    unsigned int* m_Indices;
    int m_IndicesCount;

    unsigned int m_VAO, m_VBO, m_EBO;
} TMesh;



typedef struct
{
    int m_VerticesCount;
    int m_VertexSize;
    float* m_Vertices;
    unsigned int m_VAO, m_VBO, m_EBO;

} TSimpleMesh;

typedef struct
{
    TPoint2d m_Origin;
    TSimpleMesh;
    TColor m_Color;

} TObject;

enum e_Textures {t_Water, t_DeepWater, t_Grass, t_Sand, t_Snow, t_Stone, t_Main, t_Font, t_Count};
enum e_Meshes   {mesh_Sea, mesh_Mountains, mesh_Hills, mesh_Terrain, mesh_Tower, mesh_Town, mesh_Square, mesh_GUI, mesh_Count};
enum e_SimpleMeshes {smesh_DynamicSquare, smesh_Count};

enum e_Models {m_Sea, m_Ocean, m_Plain, m_Desert, m_Taiga, m_Hills, m_Mountains, m_Tower, m_Town, m_Count};

typedef struct
{
    TPoint3d m_Position;
    TPoint3d m_Rotation;
    TPoint3d m_Scale;

    // ? Does need?
    TPoint2d m_Offset;

    TMesh* m_Mesh;
    GLuint m_Texture;

} TModel;

typedef struct
{
    char* m_Text;

    TSimpleMesh* m_Mesh;
    TColor m_Color;
    int m_Font;
    unsigned int m_IsShowed;
} TText;

typedef struct
{
    int* m_Models;
    int  m_ModelsCount;

} TTile;

typedef struct
{
    int m_Height, m_Width;
    TTile** m_Map;

} TGameMap;

typedef struct
{
    TPoint2d m_Origin;
    TPoint3d m_Rotation;
    int m_RowCount, m_ColCount;
    float dx, dy;

    TSimpleMesh;
    TColor m_Color;
    float m_LineWidth;
} TGrid;


typedef struct
{
    GLuint ID;
    GLuint projectionLocation;
    GLuint viewLocation;
    GLuint modelLocation;
    GLuint vertexLocation;
} TOpenGLProgram_base;

typedef struct
{
    TOpenGLProgram_base;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
    GLuint charIndexLocation;
} TOpenGLProgram_text;

typedef struct
{
    TOpenGLProgram_base;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
} TOpenGLProgram_main;

typedef struct
{
    TOpenGLProgram_base;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
    GLuint timeLocation;
} TOpenGLProgram_water;

typedef struct
{
    TOpenGLProgram_base;
    GLuint colorLocation;
} TOpenGLProgram_color;


typedef struct
{
    Uint32 m_MouseState;
    int x, y;
} TMouseController;

typedef struct
{
    const Uint8* m_KeyStates;

} TKeyboardController;

typedef struct
{
    int m_Width, m_Height;
    float m_modelMatrix[16];
    float m_identityMatrix[16];

    // Stuff for render to texture
    GLuint m_Framebuffer;
    GLuint m_Renderbuffer;
    GLuint m_TextureTarget;

    TOpenGLProgram_color m_glProgram_c;
    TOpenGLProgram_water m_glProgram_w;
    TOpenGLProgram_main  m_glProgram_m;
    TOpenGLProgram_text  m_glProgram_t;
} TGraphics;

typedef struct
{
    int m_IsRunning;
    int m_SelectedObj;
    int m_IsGridSelected;
        TPoint2d_i m_SelectedSquare;

        TPoint2d_i m_SelectedTile;


} TCoreState;

typedef struct
{
    float m_DeltaTime;
    float m_LastTime;
} TTimer;


typedef struct
{
    TVector3d m_Position;
    TVector3d m_Frontward;
    TVector3d m_Upward;

    TVector3d m_MoveVector;

    TRotation3d m_Rotation; // pitch yaw roll



    unsigned int m_IsOrthoProj;
    unsigned int m_IsMoveAlongAxis;
    unsigned int m_IsMoveAlongVector;
    unsigned int m_IsCameraViewAround;

    float m_OrthoProjScale;
    float m_AspectRatio;

    float m_viewMatrix[16];
    float m_projectionMatrix[16];

} TCamera;

/*
typedef struct
{
    TModel* m_Landscape;
    TModel* m_Buildings;
    TModel* m_Units;
    TModel* m_Resources;

    int m_LanscapeCount;
    int m_BuildingsCount;
    int m_UnitsCount;
    int m_ResourcesCount;

} TSceneModels;
*/

typedef struct
{
    TMesh m_Meshes[mesh_Count];
    //unsigned int m_MeshesCount;

    TSimpleMesh m_SimpleMeshes[smesh_Count];

    GLuint m_Textures[t_Count];
    //unsigned int m_TexturesCount;

    TModel* m_Models;
    unsigned int m_ModelsCount;

    TText* m_Texts;
    unsigned int m_TextsCount;

} TScene;

typedef struct
{
    TTimer m_Timer;
    TKeyboardController m_Keyboard;
    TMouseController m_Mouse;
    TCoreState m_State;
    TGraphics m_Graphics;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;

    TCamera m_Camera;

    TScene m_Scene;
    TGameMap m_Map;

    TObject* m_Objects;
    TGrid* m_Grids;

    int m_ObjectsCount;
    int m_GridsCount;

} TCore;


#endif // TYPES_H_INCLUDED
