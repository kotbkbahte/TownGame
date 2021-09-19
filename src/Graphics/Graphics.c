#include "Graphics.h"
#include "../Math/Matrix.h"
#include "../Object/Mesh.h"
#include "../Object/Model.h"
#include "../Object/Text.h"
#include "../Object/Grid.h"


int InitOpenGL(TCore* Core)
{

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to initialize OpenGL context.\n");
        return -1;
    }
    //printf("%s\n", glGetString(GL_VERSION));



    if(LoadProgram(&Core->m_Graphics.m_glProgram_c.ID, "shaders/sample.frag", "shaders/sample.vert" )  < 0)
    {
        printf("Failed load program: %s\n", "shaders/sample.frag");
        return -1;
    }
    InitProgram_c(&Core->m_Graphics.m_glProgram_c);
    if(LoadProgram(&Core->m_Graphics.m_glProgram_w.ID, "shaders/water.frag", "shaders/water.vert" ) < 0)
    {
        printf("Failed load program: %s\n", "shaders/water.frag");
        return -1;
    }
    InitProgram_w(&Core->m_Graphics.m_glProgram_w);

    if(LoadProgram(&Core->m_Graphics.m_glProgram_m.ID, "shaders/main.frag", "shaders/main.vert" ) < 0)
    {
        printf("Failed load program: %s\n", "shaders/main.frag");
        return -1;
    }
    InitProgram_m(&Core->m_Graphics.m_glProgram_m);

    if(LoadProgram(&Core->m_Graphics.m_glProgram_t.ID, "shaders/text.frag", "shaders/text.vert") < 0)
    {
        printf("Failed load program: %s\n", "shaders/text.vert");
        return -1;
    }
    InitProgram_t(&Core->m_Graphics.m_glProgram_t);

    InitCamera(&Core->m_Camera, (float)Core->m_Graphics.m_Width / (float)Core->m_Graphics.m_Height );

    loadIdentity(Core->m_Graphics.m_identityMatrix);

    return 1;
}


int InitSDL(TCore* Core)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return -1;
    }


    Core->m_Graphics.m_Width  = 1280;
    Core->m_Graphics.m_Height = 720;

    // Set SDL Attributes
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );

    Core->m_Window = SDL_CreateWindow("Convex Hull",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      Core->m_Graphics.m_Width, Core->m_Graphics.m_Height,
                                      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

    if (Core->m_Window == NULL)
    {
        return -1;
    }
    Core->m_Context = SDL_GL_CreateContext(Core->m_Window);
    if(Core->m_Context == NULL)
    {
        return -1;
    }
    return 1;
}


int InitScene(TScene* Scene)
{
    if( LoadTextures(Scene) <0 )
        return -1;

    if( InitMeshes(Scene) < 0)
        return -1;

    if( InitModels(Scene) < 0)
        return -1;

    if( InitTexts(Scene) < 0)
    return -1;



    printf("Init Scene.\n");
    return True;
}


const GLfloat squareVertices[] = {
    1.0f, 1.0f, 2.0f,
    -1.0f, 1.0f, 2.0f,
    -1.0f, -1.0f, 2.0f,
    1.0f, -1.0f, 2.0f,
};

const GLfloat squareVertices2d[] =
{
    1.0f, 0.0f, 1.0f,
    -1.0f,0.0f, 1.0f,
    -1.0f,0.0f, -1.0f,
    1.0f, 0.0f,-1.0f,
};

const GLfloat d = 0.05;
const GLfloat axisVertices[] =
{
    1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, -1.0f,
};

const GLfloat textureCoordinates[] =
{
    1.0f, 1.0f,
    0, 1.0f,
    0, 0,
    1.0f, 0,
    -1, -1,
    -1,  1,
     1,  1,
     1, -1,
};

void DrawAxis(TCore* Core)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);
    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 1.0f, 0.2f, 0.4f);

    glVertexAttribPointer(Core->m_Graphics.m_glProgram_c.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , axisVertices);

    glLineWidth(2.0f);

    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_c.vertexLocation);
    glDrawArrays(GL_LINES, 0, 2);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 0.1f, 0.8f, 0.9f);
    glDrawArrays(GL_LINES, 2, 2);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 0.1f, 0.2f, 1.0f);
    glDrawArrays(GL_LINES, 4, 2);

    glPointSize(7.0f);
    glDrawArrays(GL_POINTS, 0, 1);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 0.1f, 0.8f, 0.9f);
    glDrawArrays(GL_POINTS, 2, 1);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 0.1f, 0.2f, 1.0f);
    glDrawArrays(GL_POINTS, 4, 1);

}


void DrawSquare(TCore* Core)
{
    glBindTexture(GL_TEXTURE_2D, Core->m_Scene.m_Textures[t_Stone]);

    glUseProgram(Core->m_Graphics.m_glProgram_m.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_m.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);



    glVertexAttribPointer(Core->m_Graphics.m_glProgram_m.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_m.vertexLocation);

    glVertexAttribPointer(Core->m_Graphics.m_glProgram_m.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_m.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Draw2dSquare(TCore* Core, float x, float y, float z)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixScale(Core->m_Graphics.m_modelMatrix, 1.15f, 0.0f, 1.15f);
    matrixTranslate(Core->m_Graphics.m_modelMatrix, x, y, z);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 1.0f, 1.0f, 1.0f);


    glVertexAttribPointer(Core->m_Graphics.m_glProgram_c.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices2d);
    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_c.vertexLocation);

    glDrawArrays(GL_TRIANGLE_FAN,  0, 4);

}

void DrawSelected(TCore* Core, TModel* model, float x, float y, float z)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    DrawModelOffset(Core, model, x, y + 0.3f, z);
    Draw2dSquare(Core, x, y+0.2f, z);
}


void DrawMapColors(TCore* Core, TGameMap* map)
{
    glClearColor(0.0f, 0.01f, 0.05f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glDisable(GL_MULTISAMPLE);
        //glDisable(GL_LIGHTING);

    float dch = 1.0f / (float)(map->m_Height);
    float dcw = 1.0f / (float)(map->m_Width);
    //float ch = 0;
    //float cw = 0;

    for(int i = 0; i < map->m_Height; i++)
    {
        for(int j = 0; j < map->m_Width; j++)
        {
            {
                DrawModelOffsetColor(Core, Core->m_Scene.m_Models + map->m_Map[i][j].m_Models[0], i * 2, 0, j * 2, (i*dch), 0, (j*dcw));
            }
        }
    }

}

void DrawMap(TCore* Core, TGameMap* map)
{
    for(int i = 0; i < map->m_Height; i++)
    {
        for(int j = 0; j < map->m_Width; j++)
        {
            {
                if(i == Core->m_State.m_SelectedTile.x && j == Core->m_State.m_SelectedTile.y)
                    DrawSelected(Core, Core->m_Scene.m_Models + map->m_Map[i][j].m_Models[0], i * 2, 0, j * 2);
                else
                    DrawModelOffset(Core, Core->m_Scene.m_Models + map->m_Map[i][j].m_Models[0], i * 2, 0, j * 2);
            }

        }
    }
}


void DrawGui(TCore* Core, TMesh* mesh)
{
    static float targetA = 100.f;
    glBindTexture(GL_TEXTURE_2D, Core->m_Scene.m_Textures[t_Water]);

    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 1.0f, 1.0f, 1.0f);

        /*
        glBindVertexArray(Core->m_Scene.m_SimpleMeshes[smesh_DynamicSquare].m_VAO);
        glEnableVertexAttribArray(0);
        */


    static float coords[4][2] = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
    //printf("%.4f %.4f [%.4f] [%.4f]\n",Core->m_Camera.m_OrthoProjScale,  Core->m_Camera.m_AspectRatio, 1.0f / 16.0f, Core->m_Camera.m_AspectRatio / 16.0f);

    //for(int i = 0; i < 1; i++)
    {
        float k = Core->m_Camera.m_AspectRatio;
        float a = targetA / Core->m_Graphics.m_Height * 2.0f;
        float b = targetA / Core->m_Graphics.m_Width * 2.0f;
        float tmp = a;
        a = b;
        b = tmp;
        printf("%f %f\n", a, b);
        float verts[] = {a, b, -a, b, -a, -b, a, -b};
        loadIdentity(Core->m_Graphics.m_modelMatrix);
        //matrixTranslate(Core->m_Graphics.m_modelMatrix, -0.5f, -0.5f, 0.0f);
        //matrixScale(Core->m_Graphics.m_modelMatrix, 1.0f, Core->m_Camera.m_AspectRatio, 1.0f);
        //matrixScale(Core->m_Graphics.m_modelMatrix, 1.0f / Core->m_Camera.m_AspectRatio, 1.0f,1.0f);
        //matrixRotateZ(Core->m_Graphics.m_modelMatrix, i * 90.0f);
        //matrixScale(Core->m_Graphics.m_modelMatrix, 1.0f / 16.0f, 1.0f / 16.0f , 1.0f);
        //matrixTranslate(Core->m_Graphics.m_modelMatrix, coords[i][0] / 2.0f, coords[i][1] / 2.0f, -1.0f);
        //matrixScale(Core->m_Graphics.m_modelMatrix, Core->m_Camera.m_OrthoProjScale, Core->m_Camera.m_OrthoProjScale, 1.0f);

        glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Graphics.m_identityMatrix);
        glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Graphics.m_identityMatrix);
        glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);

        // draw mesh
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        //glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 0.0f, 0.0f, 0.0f);
        //glPointSize(4.0f);
        //glDrawArrays(GL_POINTS, 0, mesh->m_VerticesCount);
    }
    //printf("%d\n", mesh->m_VerticesCount);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderFrame(TCore* Core)
{
    glClearColor(0.0f, 0.01f, 0.05f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);


    DrawGui(Core, &Core->m_Scene.m_Meshes[mesh_GUI]);
    //DrawMesh(Core, &Core->m_Scene.m_Meshes[mesh_GUI]);
    //DrawGrid(Core, Core->m_Grids);
    DrawAxis(Core);
    DrawMap(Core, &Core->m_Map);




    glFinish();
    SDL_GL_SwapWindow(Core->m_Window);
}


GLuint LoadFile(char* FileName, const GLchar** t)
{
    int len = 8000;
    const GLchar* text = malloc(len);
    memset( (char*)text, 0, len);

    FILE *f;
    f = fopen(FileName, "rb");
    if (!f)
    {
        printf("Error load file:\n%s\n", FileName);
        return -1;
    }
    fread( (char*)text, 1, 8000, f);
    *t = text;
    fclose(f);
    return 1;

}

GLuint LoadShader(char *FileName, GLuint type)
{
    const GLchar* text = NULL;

    if (LoadFile(FileName, &text) < 0)
        return -1;

    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &text, NULL);
    glCompileShader(shader);
    GLint ok;
    GLchar log[2000];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        glGetShaderInfoLog(shader, 2000, NULL, log);
        printf("Program log: %s\n", log);
    }

    free((char*)text);
    return shader;
}


// Need to pass TOpenGLProgram either just ID?
int LoadProgram(GLuint* ID, char* frag, char* vert)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(vert, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(frag, GL_FRAGMENT_SHADER);

    // Create the program object
    *ID = glCreateProgram();
    if(*ID == 0)
        return -1;
    glAttachShader(*ID, vertexShader);
    glAttachShader(*ID, fragmentShader);

    // Link the program
    glLinkProgram(*ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Check the link status
    glGetProgramiv(*ID, GL_LINK_STATUS, &linked);
    if(!linked)
	{
	    GLint infoLen = 0;
	    glGetProgramiv(*ID, GL_INFO_LOG_LENGTH, &infoLen);
	    if(infoLen > 1)
		{
		    char* infoLog = malloc(sizeof(char) * infoLen);
		    glGetProgramInfoLog(*ID, infoLen, NULL, infoLog);
		    fprintf(stderr, "Error linking program:\n%s\n", infoLog);
		    free(infoLog);
		}

	    glDeleteProgram(*ID);
	    return -1;
	}

	return 1;
}

void InitProgram_m(TOpenGLProgram_main* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->viewLocation = glGetUniformLocation(program->ID, "view");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->textureCoordsLocation = glGetAttribLocation(program->ID, "textureCoordinates");
    program->textureLocation = glGetUniformLocation(program->ID, "texture");

    if(program->projectionLocation < 0 || program->viewLocation < 0 || program->modelLocation < 0 ||
       program->vertexLocation < 0 || program->textureCoordsLocation < 0 || program->textureLocation < 0)
    {
        printf("Error initialization GL program main.\n");
    }
}

void InitProgram_c(TOpenGLProgram_color* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->viewLocation = glGetUniformLocation(program->ID, "view");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->colorLocation = glGetUniformLocation(program->ID, "uColor");

    if(program->projectionLocation < 0 || program->viewLocation < 0 || program->modelLocation < 0 ||
       program->vertexLocation < 0 || program->colorLocation < 0)
    {
        printf("Error initialization GL program color.\n");
    }
}

void InitProgram_w(TOpenGLProgram_water* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->viewLocation = glGetUniformLocation(program->ID, "view");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->textureCoordsLocation = glGetAttribLocation(program->ID, "textureCoordinates");
    program->textureLocation = glGetUniformLocation(program->ID, "texture");
    program->timeLocation = glGetUniformLocation(program->ID, "time");

    if(program->projectionLocation < 0 || program->viewLocation < 0 || program->modelLocation < 0 ||
       program->vertexLocation < 0 || program->textureCoordsLocation < 0 || program->textureLocation < 0 || program->timeLocation < 0)
    {
        printf("Error initialization GL program water.\n");
    }
}

void InitProgram_t(TOpenGLProgram_text* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->viewLocation = glGetUniformLocation(program->ID, "view");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->textureCoordsLocation = glGetAttribLocation(program->ID, "textureCoordinates");
    program->textureLocation = glGetUniformLocation(program->ID, "texture");
    program->charIndexLocation = glGetUniformLocation(program->ID, "charIndex");


    if(program->projectionLocation < 0 || program->viewLocation < 0 || program->modelLocation < 0 ||
       program->vertexLocation < 0 || program->textureCoordsLocation < 0 || program->textureLocation < 0 || program->charIndexLocation < 0)
    {
        printf("Error initialization GL program text.\n");
    }
}



void UpdateViewportProjection(TCore* Core, int width, int height)
{
    float k = (float)width / (float)height;
    Core->m_Graphics.m_Width = width;
    Core->m_Graphics.m_Height = height;

    glViewport(0, 0, width, height);

    cam_SetProjection(&Core->m_Camera, k);

}

