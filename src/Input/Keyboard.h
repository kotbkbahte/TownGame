#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "../Core/Types.h"
#include "../Graphics/Graphics.h"
#include "../Math/Matrix.h"
#include "../Camera/Camera.h"
#include "../Object/Grid.h"
#include "../Object/Object.h"
#include "../Object/Map.h"

void kb_InitKeyboard(TKeyboardController*);
int kb_GetKeyDown(TKeyboardController*, SDL_Scancode );
int kb_GetDoubleKeyDown(TKeyboardController* keyboard, SDL_Scancode key1, SDL_Scancode key2);
void kb_KeyUp(TKeyboardController*);
void kb_KeyDown(TKeyboardController*);
void kb_KeyPressed(TCore* Core, TKeyboardController* keyboard, SDL_Keycode code);

#endif // KEYBOARD_H_INCLUDED
