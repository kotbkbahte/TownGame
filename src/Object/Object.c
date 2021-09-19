#include "Object.h"

void obj2d_InitObj(TObject* obj, float x, float y, float r, float g, float b)
{
    obj->m_Color.r = r;
    obj->m_Color.g = g;
    obj->m_Color.b = b;

    obj->m_Origin.x = x;
    obj->m_Origin.y = y;

    obj->m_Vertices = NULL;
    obj->m_VerticesCount = 0;
}

void obj2d_CreateRect(TObject* obj, float ox, float oy, float h, float w)
{
    obj->m_Origin.x = ox;
    obj->m_Origin.y = oy;

    obj->m_VerticesCount = 4;

    free(obj->m_Vertices);
    obj->m_Vertices = malloc(sizeof(float) * 2 * obj->m_VerticesCount);

    float th = h / 2.0f;
    float tw = w / 2.0f;

    obj->m_Vertices[0] = -tw;
    obj->m_Vertices[1] = -th;

    obj->m_Vertices[2] = -tw;
    obj->m_Vertices[3] =  th;

    obj->m_Vertices[4] =  tw;
    obj->m_Vertices[5] =  th;

    obj->m_Vertices[6] =  tw;
    obj->m_Vertices[7] = -th;

}

void obj2d_ObjInfo(TObject* obj)
{
    printf("Vertices: %d\n", obj->m_VerticesCount);
    printf("%f, %f\n",obj->m_Vertices[0], obj->m_Vertices[1]);
    printf("%f, %f\n",obj->m_Vertices[2], obj->m_Vertices[3]);
    printf("%f, %f\n",obj->m_Vertices[4], obj->m_Vertices[5]);
    printf("%f, %f\n",obj->m_Vertices[6], obj->m_Vertices[7]);
}

void DrawObject(TCore* Core, TObject* obj)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixTranslate(Core->m_Graphics.m_modelMatrix, obj->m_Origin.x, obj->m_Origin.y, 0);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);
    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, obj->m_Color.r, obj->m_Color.g, obj->m_Color.b);

    glVertexAttribPointer(Core->m_Graphics.m_glProgram_c.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , obj->m_Vertices);

    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_c.vertexLocation);
    glDrawArrays(GL_TRIANGLE_FAN, 0, obj->m_VerticesCount);

}
