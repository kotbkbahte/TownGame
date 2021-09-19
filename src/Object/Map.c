#include "Map.h"


void InitMap(TGameMap* Map, int h, int w)
{
    Map->m_Height = h;
    Map->m_Width = w;

    Map->m_Map = malloc(sizeof(TTile*) * Map->m_Height);

    for(int i = 0; i < Map->m_Height; i++)
    {
        Map->m_Map[i] = malloc(sizeof(TTile) * Map->m_Width);
        for(int j = 0; j < Map->m_Width; j++)
        {
            Map->m_Map[i][j].m_ModelsCount = 1;
            Map->m_Map[i][j].m_Models = malloc(sizeof(int) * Map->m_Map[i][j].m_ModelsCount);
            Map->m_Map[i][j].m_Models[0] = 0;
        }
    }
}

void GenRandomMap(TGameMap* Map)
{
    for(int i = 0; i < Map->m_Height; i++)
    {
        for(int j = 0; j < Map->m_Width; j++)
        {
            Map->m_Map[i][j].m_Models[0] = rand() % 5;
        }
    }
}

int map_ClientToCoords(TGameMap* Map, float r, float g, float b, int* i, int* j)
{
    if(g != 0)
    {
        *i = -1;
        *j = -1;
        return False;
    }
    float dch = 1.0f / (float)(Map->m_Height);
    float dcw = 1.0f / (float)(Map->m_Width);
        //printf("%f %f\n", r / dch, b / dcw);

    *i = round(r / dch);
    *j = round(b / dcw);
    return True;
}

void tile_PrintInfo(TTile* Tile, int i, int j)
{
    printf("Tile[%d, %d]: %d\n", i, j, Tile->m_ModelsCount);
}
