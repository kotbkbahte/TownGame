#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED

#include "../Core/Types.h"


int LoadTextures(TScene* scene);
int LoadTexture(const char* file_name, GLuint* texture);

#endif // TEXTURELOADER_H_INCLUDED
