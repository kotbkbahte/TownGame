#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "../Core/Types.h"
#include <math.h>
void InitMap(TGameMap* Map, int h, int w);

void GenRandomMap(TGameMap* Map);
int map_ClientToCoords(TGameMap* Map, float r, float g, float b, int* i, int* j);

void tile_PrintInfo(TTile* Tile, int i, int j);
#endif // MAP_H_INCLUDED
