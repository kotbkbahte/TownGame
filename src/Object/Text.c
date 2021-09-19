#include "Text.h"

// Need rethinking...

int InitTexts(TScene* Scene)
{
    Scene->m_TextsCount = 1;
    Scene->m_Texts = malloc(sizeof(TText) * Scene->m_TextsCount);



    text_Init(Scene, Scene->m_Texts, t_Font, "Hello World!\n");

    return 1;
}

void text_Init(TScene* Scene, TText* Text, int font, char* text)
{
    Text->m_Color = (TColor){1.0f, 1.0f, 1.0f};
    Text->m_Font  = Scene->m_Textures[font];
    Text->m_Text  = text;
    Text->m_Mesh  = &Scene->m_SimpleMeshes[smesh_DynamicSquare];

    Text->m_IsShowed = True;
}


void text_Draw(TCore* Core, TText* text)
{
    glBindTexture(GL_TEXTURE_2D, text->m_Font);

    glUseProgram(Core->m_Graphics.m_glProgram_t.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixTranslate(Core->m_Graphics.m_modelMatrix, 0, 0, 0);
    matrixScale(Core->m_Graphics.m_modelMatrix, 0.5f, 0.5f, 1.0f);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_t.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_t.viewLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_t.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);



    glBindVertexArray(text->m_Mesh->m_VAO);
    //
    const float charSize = 1 / 16.0f;
    char c = 'A';
    float xpos = (c & 0b1111) * charSize;
    float ypos = (c >> 4) * charSize;
    //float xpos = x + ch.Bearing.x * scale;
    //float ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

    float w = charSize;
    float h = charSize;
        // update VBO for each character
    float vertices[4][5] =
    {
        { 0.0f, 0.0f, 0.0f, xpos,     ypos,       },
        { 1.0f, 0.0f, 0.0f, xpos + w, ypos,       },
        { 1.0f, 1.0f, 0.0f, xpos + w, ypos + h,   },
        { 0.0f, 1.0f, 0.0f, xpos,     ypos + h,   },
    };


        // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, text->m_Font);
        // update content of VBO memory

    glBindBuffer(GL_ARRAY_BUFFER, text->m_Mesh->m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, text->m_Mesh->m_VerticesCount);


    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void text_SetText(TText* Text, char* text, int c)
{
    Text->m_Text  = text;

}

void text_SetRect(TText* Text, float x, float y)
{

}
