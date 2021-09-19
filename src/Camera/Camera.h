#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "../Core/Types.h"
#include "../Math/Matrix.h"

void InitCamera(TCamera* camera, float k);
void MoveCamera(TCamera* Camera, TKeyboardController* keyboard);


void cam_SetLookAtPosition(TCamera* camera, TVector3d vec3);
void cam_SetLookDirect(TCamera* Camera, TRotation3d rot3);


void cam_ResetProjection(TCamera* Camera);
void cam_SetProjection(TCamera* camera, float k);

void cam_SetOrtho(TCamera* camera, float bottom, float top, float left, float right, float zNear, float zFar);
void cam_SetPerspective(TCamera* camera, float fieldOfView, float aspectRatio, float zNear, float zFar);

void cam_ResetRotation(TCamera* camera);
void cam_ResetPosition(TCamera* camera);
void cam_ResetPositionRotation(TCamera* camera);

void cam_AdjustPosition(TCamera* camera, float x, float y, float z);

void cam_AdjustRotationX(TCamera* camera, float x);
void cam_AdjustRotationY(TCamera* camera, float y);
void cam_AdjustRotationZ(TCamera* camera, float z);

void cam_SetPosition(TCamera* camera, float x, float y, float z);
void cam_SetRotation(TCamera* camera, float x, float y, float z);

void cam_UpdateViewMatrix(TCamera* camera);

#endif // CAMERA_H_INCLUDED
