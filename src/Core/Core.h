#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "Types.h"
#include "../Object/OBJLoader.h"

int InitCore(TCore* Core);
void UpdateState(TCore* Core, float dt);
void InitObjects(TCore* Core);
void InitGrids(TCore* Core);
void InitCoreState(TCore* Core);

#endif // CORE_H_INCLUDED
