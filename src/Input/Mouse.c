#include "Mouse.h"


void ms_Update(TMouseController* m_Mouse)
{
    m_Mouse->m_MouseState = SDL_GetMouseState(&m_Mouse->x, &m_Mouse->y);

}


void ms_Pressed(TCore* Core, SDL_MouseButtonEvent* event)
{
    if(event->button == SDL_BUTTON_LEFT)
    {
        GLfloat rgb[3];
        DrawMapColors(Core, &Core->m_Map);
        glReadPixels(Core->m_Mouse.x, Core->m_Graphics.m_Height - Core->m_Mouse.y, 1, 1, GL_RGB, GL_FLOAT, &rgb);

        if(map_ClientToCoords(&Core->m_Map, rgb[0], rgb[1], rgb[2],
                              &Core->m_State.m_SelectedTile.x,  &Core->m_State.m_SelectedTile.y))
            tile_PrintInfo(&Core->m_Map.m_Map[Core->m_State.m_SelectedTile.x][Core->m_State.m_SelectedTile.y], Core->m_State.m_SelectedTile.x, Core->m_State.m_SelectedTile.y);

    }
    else if (event->button == SDL_BUTTON_RIGHT)
    {

    }
}
