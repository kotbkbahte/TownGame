#include "Model.h"


int InitModels(TScene* Scene)
{

    Scene->m_ModelsCount = m_Count;
    Scene->m_Models = malloc(sizeof(TModel) * Scene->m_ModelsCount);

    InitModel(Scene, &Scene->m_Models[m_Sea], mesh_Sea, t_Water, 0, 0, 0);
    InitModel(Scene, &Scene->m_Models[m_Ocean], mesh_Sea, t_DeepWater, 0 , 0, 0);
    InitModel(Scene, &Scene->m_Models[m_Plain], mesh_Terrain, t_Grass, 0, 0, 0);
    InitModel(Scene, &Scene->m_Models[m_Desert], mesh_Terrain, t_Sand, 0, 0, 0);


    InitModel(Scene, &Scene->m_Models[m_Taiga], mesh_Terrain, t_Snow, 0, 0, 0);
    InitModel(Scene, &Scene->m_Models[m_Hills], mesh_Hills, t_Grass, 0, 0, 0);
    InitModel(Scene, &Scene->m_Models[m_Mountains], mesh_Mountains, t_Stone, 0, 0, 0);

    InitModel(Scene, &Scene->m_Models[m_Tower], mesh_Tower, t_Stone, 0, 0, 0);
    InitModel(Scene, &Scene->m_Models[m_Town], mesh_Town, t_Main, 0, 0, 0);
    /*
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            d = i * 4 + j;
            if(i == 2 && j == 2)
                InitModel(Scene->m_Models + d, mesh_Mountains, t_Stone, -2  + i * 2, 0, -2 + j * 2);
            else
                InitModel(Scene->m_Models + d, mesh_Sea, t_Water, -2  + i * 2, 0,-2 + j * 2);

        }
    }
    */



    printf("Init models end.\n");
    return True;
}

void InitModel_all(TScene* Scene, TModel* Model, int mesh_type, int texture_type, float x, float y, float z, float xr, float yr, float zr, float xs, float ys, float zs)
{
    Model->m_Position.x = x;
    Model->m_Position.y = y;
    Model->m_Position.z = z;

    Model->m_Rotation.x = xr;
    Model->m_Rotation.y = yr;
    Model->m_Rotation.z = zr;

    Model->m_Scale.x = xs;
    Model->m_Scale.y = ys;
    Model->m_Scale.z = zs;

    Model->m_Texture = Scene->m_Textures[texture_type];

    Model->m_Mesh = &Scene->m_Meshes[mesh_type];
}


void DrawModel(TCore* Core, TModel* model)
{
    glBindTexture(GL_TEXTURE_2D, model->m_Texture);

    glUseProgram(Core->m_Graphics.m_glProgram_m.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixTranslate(Core->m_Graphics.m_modelMatrix, model->m_Position.x, model->m_Position.y, model->m_Position.z);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);


    glBindVertexArray(model->m_Mesh->m_VAO);

    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, model->m_Mesh->m_VerticesCount);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawModelOffsetColor(TCore* Core, TModel* model, float ox, float oy, float oz, float r, float g, float b)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixTranslate(Core->m_Graphics.m_modelMatrix,  ox + model->m_Position.x, oy+  model->m_Position.y,oz+ model->m_Position.z);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, r, g, b);

    glBindVertexArray(model->m_Mesh->m_VAO);

    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, model->m_Mesh->m_VerticesCount);

    glBindVertexArray(0);
}

void DrawModelOffset(TCore* Core, TModel* model, float ox, float oy, float oz)
{
    glBindTexture(GL_TEXTURE_2D, model->m_Texture);

    glUseProgram(Core->m_Graphics.m_glProgram_m.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixTranslate(Core->m_Graphics.m_modelMatrix,  ox + model->m_Position.x, oy+  model->m_Position.y,oz+ model->m_Position.z);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);


    glBindVertexArray(model->m_Mesh->m_VAO);

    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, model->m_Mesh->m_VerticesCount);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawModelScaled(TCore* Core, TModel* model, float x, float y, float z, float sx , float sy, float sz)
{
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixScale(Core->m_Graphics.m_modelMatrix, sx, sy, sz);
    matrixTranslate(Core->m_Graphics.m_modelMatrix, x +  model->m_Position.x, y +  model->m_Position.y, z +model->m_Position.z);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 1.0f, 1.0f, 1.0f);

    glBindVertexArray(model->m_Mesh->m_VAO);

    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, model->m_Mesh->m_VerticesCount);

    glBindVertexArray(0);
}

