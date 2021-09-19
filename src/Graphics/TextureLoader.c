#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../SideSource/stb_image.h"

int LoadTextures(TScene* Scene)
{
    LoadTexture("assets/textures/water_full_opacity.png", &Scene->m_Textures[t_Water]);
    LoadTexture("assets/textures/water_3.png", &Scene->m_Textures[t_DeepWater]);
    LoadTexture("assets/textures/stone16_f.png", &Scene->m_Textures[t_Stone]);
    LoadTexture("assets/textures/grass.png", &Scene->m_Textures[t_Grass]);
    LoadTexture("assets/textures/sand.png", &Scene->m_Textures[t_Sand]);
    LoadTexture("assets/textures/Texture.png", &Scene->m_Textures[t_Main]);
    LoadTexture("assets/textures/snow.png", &Scene->m_Textures[t_Snow]);

    LoadTexture("assets/fonts/Consolas.png", &Scene->m_Textures[t_Font]);


    return True;
}

//int LoadTexture(const char* file_name, TScene* scene, int texture_type)
int LoadTexture(const char* file_name, GLuint* texture)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D); ??
    }
    else
    {
        printf("Failed load texture: %s\n", file_name);
        stbi_image_free(data);
        return False;
    }
    stbi_image_free(data);
    return True;
}


void SetupTexture(GLuint* texture, int w, int h)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}
