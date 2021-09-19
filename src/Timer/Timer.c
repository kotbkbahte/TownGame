#include "Timer.h"

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

void Tick(TTimer* m_Timer)
{
    m_Timer->m_DeltaTime = (SDL_GetTicks() - m_Timer->m_LastTime) * (TARGET_FPS / 1000.0f);

    if (m_Timer->m_DeltaTime > TARGET_DELTATIME)
        m_Timer->m_DeltaTime = TARGET_DELTATIME;

    m_Timer->m_LastTime = SDL_GetTicks();
}



