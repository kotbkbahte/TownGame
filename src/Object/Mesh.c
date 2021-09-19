#include "Mesh.h"

const GLfloat squareVert2d[] =
{
     0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
};

void DrawMesh(TCore* Core, TMesh* mesh)
{
    glBindTexture(GL_TEXTURE_2D, Core->m_Scene.m_Textures[t_Water]);

    glUseProgram(Core->m_Graphics.m_glProgram_m.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    //matrixTranslate(Core->m_Graphics.m_modelMatrix, grid->m_Origin.x, grid->m_Origin.y, 0);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

    //glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 1.0f, 1.0f, 1.0f);

    // draw mesh
    glBindVertexArray(mesh->m_VAO);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, mesh->m_VerticesCount);


    glPointSize(4.0f);
    glDrawArrays(GL_POINTS, 0, mesh->m_VerticesCount);
    //printf("%d\n", mesh->m_VerticesCount);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


int InitMeshes(TScene* Scene)
{
    LoadMeshFromObj(&Scene->m_Meshes[mesh_Sea], "assets/models/Water_f.obj");
    LoadMeshFromObj(&Scene->m_Meshes[mesh_Mountains], "assets/models/Mountains.obj");
    LoadMeshFromObj(&Scene->m_Meshes[mesh_Terrain], "assets/models/Terrain_1.obj");
    LoadMeshFromObj(&Scene->m_Meshes[mesh_Tower], "assets/models/Tower_f1.obj");
    LoadMeshFromObj(&Scene->m_Meshes[mesh_Town], "assets/models/Town.obj");
    LoadMeshFromObj(&Scene->m_Meshes[mesh_Hills], "assets/models/Hill.obj");

    CreateSimpleMesh(&Scene->m_SimpleMeshes[smesh_DynamicSquare], 4, 3, (float*)squareVert2d, GL_DYNAMIC_DRAW);

    LoadMeshFromObj(&Scene->m_Meshes[mesh_GUI], "assets/models/Corner_3.obj");

    return True;
}



int LoadMeshFromObj(TMesh* Mesh, const char* file_name)
{
    if(!LoadObj(file_name, &Mesh->m_Vertices, &Mesh->m_VerticesCount))
    {
        printf("Error load Mesh: %s.\n", file_name);
        return False;
    }

    SetupMesh_pnt(Mesh);

    return True;
}

void CreateMesh(TMesh* mesh, unsigned int* indices, int indices_count, TVertex* vertices, int vertices_count)
{
    mesh->m_Vertices = vertices;
    mesh->m_VerticesCount = vertices_count;

    /*
    mesh->m_Indices = indices;
    mesh->m_IndicesCount = indices_count;

    mesh->m_Textures = textures;
    mesh->m_TexturesCount = textures_count;
    */

    SetupMesh_pnt(mesh);
}

void CreateSimpleMesh(TSimpleMesh* Mesh, int vert_count, int vert_size , float* vertices, GLenum usage)
{
    /*
    printf("Here!\n");
    for(int i = 0; i < vert_count * (vert_size + 2); i++ )
    {
        printf("%f \n", vertices[i]);
    } exit(0);
    */

    Mesh->m_Vertices = vertices;
    Mesh->m_VertexSize = vert_size; // for xyz coords : xyz => 3, xy => 2
    Mesh->m_VerticesCount = vert_count;

    SetupSimpleMesh(Mesh, usage);
}


void SetupSimpleMesh(TSimpleMesh* Mesh, GLenum usage)
{
    glGenVertexArrays(1, &Mesh->m_VAO);
    glGenBuffers(1, &Mesh->m_VBO);
    //glGenBuffers(1, &Mesh->m_EBO);

    glBindVertexArray(Mesh->m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Mesh->m_VBO);
    glBufferData(GL_ARRAY_BUFFER, Mesh->m_VerticesCount * (Mesh->m_VertexSize + 2) * sizeof(float), Mesh->m_Vertices, usage);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, Mesh->m_VertexSize, GL_FLOAT, GL_FALSE,  (Mesh->m_VertexSize + 2) * sizeof(float), (void*)0);
    //glVertexAttribPointer()

    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,  (Mesh->m_VertexSize + 2) * sizeof(float), (void*)(Mesh->m_VertexSize * sizeof(float) ));


    //glDeleteBuffers(1, &Mesh->m_VBO);
    //glDeleteBuffers(1, &Mesh->m_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SetupMesh_pnt(TMesh* mesh)
{

    glGenVertexArrays(1, &mesh->m_VAO);
    glGenBuffers(1, &mesh->m_VBO);
    glGenBuffers(1, &mesh->m_EBO);


    glBindVertexArray(mesh->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh->m_VerticesCount * sizeof(TVertex), mesh->m_Vertices, GL_STATIC_DRAW);

    /*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_IndicesCount * sizeof(unsigned int),
                 mesh->m_Indices, GL_STATIC_DRAW);
    */

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TVertex), (void*)offsetof(TVertex, m_TexCoord));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex), (void*)offsetof(TVertex, m_Normal));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Needs to free all arrays? m_Vertices / m_Indices / m_Normals
}


