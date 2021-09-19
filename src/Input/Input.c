#include "Input.h"
#include "../Math/Matrix.h"

void HandleEvents(TCore* Core)
{
    SDL_Event event;
    while ( SDL_PollEvent(&event) )
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Core->m_State.m_IsRunning = False;
                break;

            case SDL_MOUSEWHEEL:
                {
                    static float i;
                    i = (float)( (event.wheel.y > 0) - (event.wheel.y < 0));
                    Core->m_Camera.m_OrthoProjScale += 0.15f * (i * Core->m_Camera.m_OrthoProjScale) ;
                    cam_ResetProjection(&Core->m_Camera);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                {
                    ms_Pressed(Core, &event.button);
                }
                break;
            case SDL_MOUSEMOTION:
                {
                    Core->m_Mouse.x = event.motion.x;
                    Core->m_Mouse.y = event.motion.y;
                }
                break;

            case SDL_KEYUP:
                kb_KeyUp(&Core->m_Keyboard);
                break;

            case SDL_KEYDOWN:
                kb_KeyDown(&Core->m_Keyboard);
                kb_KeyPressed(Core, &Core->m_Keyboard, event.key.keysym.sym);
                break;

            case SDL_WINDOWEVENT:
                switch(event.window.event)
                {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    UpdateViewportProjection(Core, event.window.data1, event.window.data2);
                    //Core->m_Graphics.m_Width  = event.window.data1;
                    //Core->m_Graphics.m_Height = event.window.data2;

                    //glViewport(0, 0, Core->m_Graphics.m_Width, Core->m_Graphics.m_Height);
                    //float k = Core->m_Graphics.m_Width / (float)Core->m_Graphics.m_Height;
                    //glOrtho(-k, k, -1,1, -1,1);
                    //cam_SetOrtho(&Core->m_Camera, -1, 1, -k, k, -5.0f, 5.0f);

                }
                break;
                }
                break;


        }
    }
}


