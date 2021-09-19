#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED


#include "../Core/Core.h"
#include "../Camera/Camera.h"
#include "TextureLoader.h"
int InitSDL(TCore*);
int InitOpenGL(TCore*);
int InitScene(TScene*);

void UpdateViewportProjection(TCore*, int, int);

void RenderFrame(TCore* Core);

// Draw stuff
void DrawSquare(TCore* Core);
void DrawMapColors(TCore* Core, TGameMap* map);


// Load stuff
GLuint LoadShader(char*, GLuint);
GLuint LoadFile(char*, const GLchar**);

int LoadProgram(GLuint*, char*, char*);

void InitProgram_m(TOpenGLProgram_main*);
void InitProgram_w(TOpenGLProgram_water*);
void InitProgram_c(TOpenGLProgram_color*);
void InitProgram_t(TOpenGLProgram_text*);


void UseProgram_m(TOpenGLProgram_main*);
void UseProgram_w(TOpenGLProgram_water*);
void UseProgram_c(TOpenGLProgram_color*);

#endif // GRAPHICS_H_INCLUDED
