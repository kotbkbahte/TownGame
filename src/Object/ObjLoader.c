#include "ObjLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintVertices(TVertex* vertices, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d: %.2f %.2f %.2f | %.2f %.2f %.2f | %.2f %.2f |\n", i,
                                                         vertices[i].m_Position.x, vertices[i].m_Position.y, vertices[i].m_Position.z,
                                                         vertices[i].m_Normal.x, vertices[i].m_Normal.y, vertices[i].m_Normal.z,
                                                         vertices[i].m_TexCoord.x, vertices[i].m_TexCoord.y);
    }
}

int LoadObj(const char* file_name, TVertex** vertices, int* vertices_count)
{
    FILE *fp = fopen(file_name, "r");
    if(!fp)
    {
        printf("Error load model from file: %s\n", file_name);
        return False;
    }

    // Vertex portions
    TPoint3d* vertex_positions = malloc(sizeof(TPoint3d) * MAX_VERTEX_COUNT);
    int vp_size = 1;
    TPoint2d* vertex_texcoords = malloc(sizeof(TPoint2d) * MAX_VERTEX_COUNT);
    int vt_size = 1;
    TPoint3d* vertex_normals   = malloc(sizeof(TPoint3d) * MAX_VERTEX_COUNT);
    int vn_size = 1;

    int p_index = 0;
    int t_index = 0;
    int n_index = 0;

    // Face vectors;
    int* vertex_positions_indicies = malloc(sizeof(int) * MAX_VERTEX_COUNT);
    int* vertex_texcoords_indicies = malloc(sizeof(int) * MAX_VERTEX_COUNT);
    int* vertex_normals_indicies   = malloc(sizeof(int) * MAX_VERTEX_COUNT);

    int indices = 0;
    int f = 1;

    // Vertex Array

    char line[256];
    char* prefix;
    char* nums;

    TPoint3d temp_vec3;
    TPoint2d temp_vec2;
    int temp_position, temp_texture, temp_normal;


    while(ReadLine(line, 256, fp))
    {
        prefix = strtok(line, " ");

        if(strcmp(prefix, "#") == 0)
        {

        }
        else if(strcmp(prefix,"o") == 0)
        {

        }
        else if(strcmp(prefix, "use_mtl") == 0)
        {

        }
        else if(strcmp(prefix, "v") == 0) // Vertex position
        {

            sscanf(line+2, "%f %f %f", &temp_vec3.x, &temp_vec3.y, &temp_vec3.z);

            vertex_positions[p_index].x = temp_vec3.x;
            vertex_positions[p_index].y = temp_vec3.y;
            vertex_positions[p_index].z = temp_vec3.z;
            p_index++;
            if(p_index == MAX_VERTEX_COUNT * vp_size)
            {
                vp_size +=1;
                vertex_positions = realloc(vertex_positions, sizeof(TPoint3d) * MAX_VERTEX_COUNT * vp_size);
            }

        }
        else if(strcmp(prefix, "vt") == 0)
        {
            sscanf(line+3, "%f %f", &temp_vec2.x, &temp_vec2.y);
            //printf("%f %f\n", temp_vec2.x, temp_vec2.y);

            vertex_texcoords[t_index].x = temp_vec2.x;
            vertex_texcoords[t_index].y = temp_vec2.y;
            t_index++;
            if(t_index == MAX_VERTEX_COUNT * vt_size)
            {
                vt_size +=1;
                vertex_texcoords = realloc(vertex_texcoords, sizeof(TPoint2d) *  MAX_VERTEX_COUNT * vt_size);
            }
        }
        else if(strcmp(prefix, "vn") == 0) // Vertex normals
        {
            sscanf(line+3, "%f %f %f", &temp_vec3.x, &temp_vec3.y, &temp_vec3.z);
            vertex_normals[n_index].x = temp_vec3.x;
            vertex_normals[n_index].y = temp_vec3.y;
            vertex_normals[n_index].z = temp_vec3.z;
            n_index++;
            if(n_index == MAX_VERTEX_COUNT * vn_size)
            {
                vn_size +=1;
                vertex_normals = realloc(vertex_normals, sizeof(TPoint3d) * MAX_VERTEX_COUNT * vn_size);
            }
        }
        else if(strcmp(prefix, "f") == 0)
        {

            nums = strtok(NULL, " ");
            while(nums)
            {
                //printf("%d: %s\n",indices, nums);
                sscanf(nums, "%d/%d/%d", &temp_position, &temp_texture, &temp_normal);
                vertex_positions_indicies[indices] = temp_position;
                vertex_texcoords_indicies[indices] = temp_texture;
                vertex_normals_indicies[indices] = temp_normal;
                indices++;

                if(indices == MAX_VERTEX_COUNT * f)
                {
                    f++;
                    vertex_positions_indicies = realloc(vertex_positions_indicies, sizeof(int) * MAX_VERTEX_COUNT * f);
                    vertex_texcoords_indicies = realloc(vertex_texcoords_indicies, sizeof(int) * MAX_VERTEX_COUNT * f);
                    vertex_normals_indicies   = realloc(vertex_normals_indicies, sizeof(int) * MAX_VERTEX_COUNT * f);
                }

                nums = strtok(NULL, " ");

            }

        }
        else
        {

        }
    }

    for(int i = 0; i < p_index; i++)
    {
        //printf("P[%d]: %f %f %f\n", i, vertex_positions[i].x, vertex_positions[i].y, vertex_positions[i].z);
    }
    for(int i = 0; i < t_index; i++)
    {
        //printf("T[%d]: %f %f\n", i, vertex_texcoords[i].x, vertex_texcoords[i].y);
    }
    for(int i = 0; i < n_index; i++)
    {
        //printf("N[%d]: %f %f %f\n",i, vertex_normals[i].x, vertex_normals[i].y, vertex_normals[i].z);
    }
    for(int i = 0; i < indices; i++)
    {
        //printf("PI[%d]: %d\n", i, vertex_positions_indicies[i]);
    }

    //printf("%d \n", indices);
    *vertices_count = indices;
    *vertices = malloc( sizeof(TVertex) * (indices) );

    for(int i = 0; i < indices; i++)
    {
        //printf("%d\n", i);
        (*vertices)[i].m_Position = vertex_positions[vertex_positions_indicies[i] - 1];
        (*vertices)[i].m_TexCoord = vertex_texcoords[vertex_texcoords_indicies[i] - 1];
        (*vertices)[i].m_Normal   = vertex_normals[vertex_normals_indicies[i] - 1];
        (*vertices)[i].m_Color.x  = 1.0f;
        (*vertices)[i].m_Color.y  = 1.0f;
        (*vertices)[i].m_Color.z  = 1.0f;
    }

    free(vertex_positions);
    free(vertex_texcoords);
    free(vertex_normals);

    free(vertex_positions_indicies);
    free(vertex_texcoords_indicies);
    free(vertex_normals_indicies);

    // !!
    fclose(fp);
    return True;
}


int ReadLine(char *buff, int size, FILE *fp)
{
  buff[0] = '\0';
  buff[size - 1] = '\0';             /* mark end of buffer */
  char *tmp;

  if (fgets(buff, size, fp) == NULL) {
      *buff = '\0';                   /* EOF */
      return False;
  }
  else {
      // remove newline
      if ((tmp = strrchr(buff, '\n')) != NULL)
      {
          *tmp = '\0';
      }
  }
  return True;
}


