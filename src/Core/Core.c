#include "../Graphics/Graphics.h"

#include "../Input/Input.h"
#include "../Object/Object.h"
#include "../Object/Grid.h"
#include "../Camera/Camera.h"
#include "../Object/Mesh.h"
#include "../Object/Model.h"
#include "../Math/Vector.h"


int InitCore(TCore* Core)
{
    Core->m_State.m_IsRunning = False;

    if(InitSDL(Core) < 0)
    {
        printf("Error while init SDL.\n");
        return -1;
    }

    if(InitOpenGL(Core) < 0)
    {
        printf("Error while init Open GL.\n");
        return -1;
    }

    if(InitScene(&Core->m_Scene) < 0)
    {
        printf("Error while init Scene.\n");
        return -1;
    }

    InitMap(&Core->m_Map, 8, 8);
    GenRandomMap(&Core->m_Map);

    InitObjects(Core);
    InitGrids(Core);

    InitCoreState(Core);

    kb_InitKeyboard(&Core->m_Keyboard);

    return 1;
}

void UpdateState(TCore* Core, float dt)
{
    //system("cls");
    //cam_Info(&Core->m_Camera);


    if(kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_ESCAPE))
    {
        Core->m_State.m_IsRunning = False;
        return;
    }

    grid_Update_cr(Core->m_Grids, kb_GetDoubleKeyDown(&Core->m_Keyboard, SDL_SCANCODE_C, SDL_SCANCODE_EQUALS) -
                    kb_GetDoubleKeyDown(&Core->m_Keyboard, SDL_SCANCODE_C, SDL_SCANCODE_MINUS) ,
                   kb_GetDoubleKeyDown(&Core->m_Keyboard, SDL_SCANCODE_R, SDL_SCANCODE_EQUALS) -
                    kb_GetDoubleKeyDown(&Core->m_Keyboard, SDL_SCANCODE_R, SDL_SCANCODE_MINUS));



    MoveCamera(&Core->m_Camera, &Core->m_Keyboard);






}


void InitObjects(TCore* Core)
{
    Core->m_ObjectsCount = 1;
    Core->m_Objects = malloc(sizeof(TObject) * Core->m_ObjectsCount);

    obj2d_InitObj(Core->m_Objects, 0, 0, 0.4f, 1.0f, 0.0f);
    obj2d_CreateRect(Core->m_Objects, 0, 0, 0.05f, 0.05f);

}

void InitGrids(TCore* Core)
{
    Core->m_GridsCount = 1;
    Core->m_Grids = malloc(sizeof(TGrid) * Core->m_GridsCount);

    grid_Init(Core->m_Grids, 0, 0, 5, 5, 0.3f, 0.3f, 2.0f ,random_color);

}

void InitCoreState(TCore* Core)
{
    Core->m_State.m_IsRunning = True;
    Core->m_State.m_IsGridSelected = True;
}


