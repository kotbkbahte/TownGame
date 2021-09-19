#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "../Core/Types.h"
#include "../Math/Matrix.h"



int InitTexts(TScene* Scene);


void text_Init(TScene* Scene, TText* Text, int font, char* text);

void text_Draw(TCore* Core, TText* text);
void DrawText_Info(TCore* Core);

void text_SetText(TText* Text, char* text, int c);
void text_SetRect(TText* Text, float x, float y);




#endif // TEXT_H_INCLUDED
