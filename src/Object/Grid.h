#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED


#include "../Core/Types.h"
#include "../Math/Matrix.h"

void DrawGrid(TCore* Core, TGrid* grid);
void DrawSelectedGrid(TCore* Core, TGrid* grid, int i, int j);

void grid_Init(TGrid* grid, float ox, float oy, int row, int col, float dx, float dy, float width, float r, float g, float b);

void grid_Update(TGrid* grid);

void grid_Update_cr(TGrid* grid, int dcol, int drow);

int grid_GetSelectedSquare(TGrid* grid, float x, float y, int* col, int* row);

//void grid_Update_dxdy(TGrid* grid, float dx, float dy);
//void grid_Update_dx(TGrid* grid, float dx, float dy);
//void grid_Update_dy(TGrid* grid, float dx, float dy);



#endif // GRID_H_INCLUDED
