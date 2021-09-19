#include "Keyboard.h"


int kb_GetKeyDown(TKeyboardController* keyboard, SDL_Scancode key)
{
    return keyboard->m_KeyStates[key];
}

int kb_GetDoubleKeyDown(TKeyboardController* keyboard, SDL_Scancode key1, SDL_Scancode key2)
{
    return (keyboard->m_KeyStates[key1]) && (keyboard->m_KeyStates[key2]) ;
}

void kb_InitKeyboard(TKeyboardController* keyboard)
{
    keyboard->m_KeyStates = SDL_GetKeyboardState(NULL);
}

void kb_KeyUp(TKeyboardController* keyboard)
{
    keyboard->m_KeyStates = SDL_GetKeyboardState(NULL);
}

void kb_KeyDown(TKeyboardController* keyboard)
{
    keyboard->m_KeyStates = SDL_GetKeyboardState(NULL);
}

void kb_KeyPressed(TCore* Core, TKeyboardController* keyboard, SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_LCTRL:
        {
            Core->m_Camera.m_IsCameraViewAround = !Core->m_Camera.m_IsCameraViewAround;
        }
        break;
    case SDLK_r:
        cam_ResetPositionRotation(&Core->m_Camera);
        break;
    case SDLK_q:
        Core->m_Camera.m_IsMoveAlongAxis = !Core->m_Camera.m_IsMoveAlongAxis;
        break;
    case SDLK_v:
        Core->m_Camera.m_IsMoveAlongVector = !Core->m_Camera.m_IsMoveAlongVector;
        break;

    case SDLK_KP_5:
        Core->m_Camera.m_IsOrthoProj = !Core->m_Camera.m_IsOrthoProj;
        cam_SetProjection(&Core->m_Camera, (float)Core->m_Graphics.m_Width/(float)Core->m_Graphics.m_Height);
        break;
    default:
        break;
    }
}
