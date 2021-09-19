#include <stdio.h>
#include <stdlib.h>

#include "src/Core/Core.h"
#include "src/Graphics/Graphics.h"
#include "src/Input/Input.h"
#include "src/Timer/Timer.h"
TCore Core;

int main(int argc, char** argv)
{
    if(InitCore(&Core) < 0)
        printf("Error init core.\n");

    while(Core.m_State.m_IsRunning)
    {
        HandleEvents(&Core);
        UpdateState(&Core, Core.m_Timer.m_DeltaTime);
        RenderFrame(&Core);

        Tick(&Core.m_Timer);
    }
    SDL_Quit();

    return 0;
}
