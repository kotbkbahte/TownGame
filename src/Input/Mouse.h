#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "../Core/Types.h"
#include "../Object/Map.h"
#include "../Graphics/Graphics.h"
void ms_Update(TMouseController* m_Mouse);

void ms_Pressed(TCore* Core, SDL_MouseButtonEvent* event);
#endif // MOUSE_H_INCLUDED
