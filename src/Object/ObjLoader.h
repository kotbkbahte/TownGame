#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include <stdio.h>
#include "../Core/Types.h"

#define MAXLINE 128

int ReadLine(char *,int ,FILE *);
int LoadObj(const char* file_name, TVertex** vertices, int* vertices_count);

#endif // OBJLOADER_H_INCLUDED
