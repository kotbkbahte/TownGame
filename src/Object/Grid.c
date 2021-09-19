#include "Grid.h"


void DrawSelectedGrid(TCore* Core, TGrid* grid, int i, int j)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);

    float tmpx = grid->dx * ((float)i - grid->m_ColCount / 2.0f);
    float tmpy = grid->dy * ((float)j - grid->m_RowCount / 2.0f);

    float vert[8] = {tmpx, tmpy, tmpx, tmpy+grid->dy, tmpx + grid->dx, tmpy + grid->dy, tmpx + grid->dx, tmpy};

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, 0.0f, 0.0f, 0.0f);

    glVertexAttribPointer(Core->m_Graphics.m_glProgram_c.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , vert);
    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_c.vertexLocation);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void DrawGrid(TCore* Core, TGrid* grid)
{
    glUseProgram(Core->m_Graphics.m_glProgram_c.ID);
    loadIdentity(Core->m_Graphics.m_modelMatrix);
    matrixTranslate(Core->m_Graphics.m_modelMatrix, grid->m_Origin.x, grid->m_Origin.y, 0);

    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.projectionLocation, 1, GL_FALSE, Core->m_Camera.m_projectionMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.viewLocation, 1, GL_FALSE, Core->m_Camera.m_viewMatrix);
    glUniformMatrix4fv(Core->m_Graphics.m_glProgram_c.modelLocation, 1, GL_FALSE, Core->m_Graphics.m_modelMatrix);

    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation, grid->m_Color.r, grid->m_Color.g, grid->m_Color.b);

    glVertexAttribPointer(Core->m_Graphics.m_glProgram_c.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , grid->m_Vertices);
    glEnableVertexAttribArray(Core->m_Graphics.m_glProgram_c.vertexLocation);

    glLineWidth(grid->m_LineWidth);
    glDrawArrays(GL_LINES, 4, grid->m_VerticesCount);


    glUniform3f(Core->m_Graphics.m_glProgram_c.colorLocation,0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


void grid_Init(TGrid* grid, float ox, float oy, int row, int col, float dx, float dy, float width, float r, float g, float b)
{
    grid->m_Origin.x = ox;
    grid->m_Origin.y = oy;

    grid->m_RowCount = row;
    grid->m_ColCount = col;

    grid->dx = dx;
    grid->dy = dy;

    grid->m_LineWidth = width;

    grid->m_Color.r = r;
    grid->m_Color.g = g;
    grid->m_Color.b = b;

    grid->m_VerticesCount = (grid->m_ColCount + grid->m_RowCount  + 2) * 2;
    grid->m_Vertices = malloc(sizeof( float ) * 2 * (grid->m_VerticesCount + 4) ) ;


    float tmpx = - grid->dx * ( (float) grid->m_ColCount / 2.0f );
    float tmpy = - grid->dy * ( (float) grid->m_RowCount / 2.0f );

    int i = 0;

    grid->m_Vertices[0] =  tmpx;
    grid->m_Vertices[1] =  tmpy;

    grid->m_Vertices[2] =  tmpx;
    grid->m_Vertices[3] = -tmpy;

    grid->m_Vertices[4] = -tmpx;
    grid->m_Vertices[5] = -tmpy;

    grid->m_Vertices[6] = -tmpx;
    grid->m_Vertices[7] =  tmpy;


    // float i = - tmpx ; i <= tmpx; i+=dx
    // columns
    for(i = 2; i < grid->m_ColCount + 3; i++)
    {
        // x pos
        grid->m_Vertices[4 * i + 0] = tmpx;
        // y pos
        grid->m_Vertices[4 * i + 1] =  tmpy;

        grid->m_Vertices[4 * i + 2] = tmpx;

        grid->m_Vertices[4 * i + 3] = -tmpy;

        tmpx+= grid->dx ;

    }
    tmpx = - grid->dx * ( (float) grid->m_ColCount / 2.0f );
    for(i = grid->m_ColCount + 3; i < (grid->m_RowCount + grid->m_ColCount + 4); i++)
    {
        // x pos
        grid->m_Vertices[4 * i + 0] = -tmpx;
        // y pos
        grid->m_Vertices[4 * i + 1] =  tmpy;

        grid->m_Vertices[4 * i + 2] = tmpx;

        grid->m_Vertices[4 * i + 3] = tmpy;

        tmpy+= grid->dy;
    }

}
void grid_Update(TGrid* grid)
{
    grid->m_VerticesCount = (grid->m_ColCount + grid->m_RowCount  + 2) * 2;

    free(grid->m_Vertices);
    grid->m_Vertices = malloc(sizeof( float ) * 2 * (grid->m_VerticesCount + 4) ) ;


    float tmpx = - grid->dx * ( (float) grid->m_ColCount / 2.0f );
    float tmpy = - grid->dy * ( (float) grid->m_RowCount / 2.0f );

    int i = 0;

    grid->m_Vertices[0] =  tmpx;
    grid->m_Vertices[1] =  tmpy;

    grid->m_Vertices[2] =  tmpx;
    grid->m_Vertices[3] = -tmpy;

    grid->m_Vertices[4] = -tmpx;
    grid->m_Vertices[5] = -tmpy;

    grid->m_Vertices[6] = -tmpx;
    grid->m_Vertices[7] =  tmpy;


    // float i = - tmpx ; i <= tmpx; i+=dx
    // columns
    for(i = 2; i < grid->m_ColCount + 3; i++)
    {
        // x pos
        grid->m_Vertices[4 * i + 0] = tmpx;
        // y pos
        grid->m_Vertices[4 * i + 1] =  tmpy;

        grid->m_Vertices[4 * i + 2] = tmpx;

        grid->m_Vertices[4 * i + 3] = -tmpy;

        tmpx+= grid->dx ;

    }
    tmpx = - grid->dx * ( (float) grid->m_ColCount / 2.0f );
    for(i = grid->m_ColCount + 3; i < (grid->m_RowCount + grid->m_ColCount + 4); i++)
    {
        // x pos
        grid->m_Vertices[4 * i + 0] = -tmpx;
        // y pos
        grid->m_Vertices[4 * i + 1] =  tmpy;

        grid->m_Vertices[4 * i + 2] = tmpx;

        grid->m_Vertices[4 * i + 3] = tmpy;

        tmpy+= grid->dy;
    }

}


void grid_Update_cr(TGrid* grid, int dcol, int drow)
{
    if(dcol==0 && drow == 0)
        return;
    grid->m_RowCount += drow;
    grid->m_ColCount += dcol;

    if(grid->m_RowCount < 1)
        grid->m_RowCount = 1;
    if(grid->m_ColCount < 1)
        grid->m_ColCount = 1;

    grid_Update(grid);
}

void grid_snapTo(TGrid* grid, float ox, float oy)
{

}

int grid_GetSelectedSquare(TGrid* grid, float x, float y, int* col, int* row)
{
    *col = floorf( x / grid->dx + grid->m_ColCount / 2.0f);
    *row = floorf( y / grid->dy + grid->m_RowCount / 2.0f);
    if( (*col) < 0  || (*col) > grid->m_ColCount - 1 || (*row) < 0 || (*row) > grid->m_ColCount - 1 )
    {
        return 0;
    }
    return 1;
}

