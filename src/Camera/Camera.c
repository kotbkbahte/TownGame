#include "Camera.h"
#include "../Input/Keyboard.h"

#define SQRT_2 1.41421356237


void InitCamera(TCamera* Camera, float k)
{
    cam_SetOrtho(Camera, -1, 1, -k, k, -50.0f, 50.0f);

    Camera->m_IsOrthoProj = True;
    Camera->m_IsMoveAlongAxis = False;
    Camera->m_IsMoveAlongVector = False;
    Camera->m_IsCameraViewAround = False;
    Camera->m_OrthoProjScale = 1.0f;
    Camera->m_AspectRatio = k;

    Camera->m_Position  = math_Vector3d(0.0f, 0.0f, 3.0f);
    Camera->m_Frontward = math_Vector3d(0.0f, 0.0f, -1.0f);
    Camera->m_Upward    = math_Vector3d(0.0f, 1.0f, 0.0f);
    Camera->m_MoveVector= (TVector3d){1.0f, 0.0f, 1.0f};
    Camera->m_Rotation  = (TRotation3d){-45.0f, -45.0f, 0};

    cam_SetLookDirect(Camera, Camera->m_Rotation);
}

void MoveCamera(TCamera* Camera, TKeyboardController* keyboard)
{
    const float cameraSpeed = 0.05f; // adjust accordingly
    TVector3d temp;

    if(Camera->m_IsMoveAlongVector)
    {
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_D))
        {
            temp = math_v3dNormalize(&Camera->m_MoveVector);
            temp = math_v3dScale(&temp, cameraSpeed);
            cam_AdjustPosition(Camera, temp.x, temp.y, temp.z);

            //printf("D->");
            //math_v3dPrint(&temp);
        }
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_A))
        {
            temp = math_v3dNormalize(&Camera->m_MoveVector);
            temp = math_v3dScale(&temp, cameraSpeed);
            cam_AdjustPosition(Camera, -temp.x, -temp.y, -temp.z);

            //printf("A->");
            //math_v3dPrint(&temp);
        }
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_W))
        {
            temp = math_v3dCross(&Camera->m_MoveVector, &(TVector3d){0.0f, 1.0f, 0.0f} );
            temp = math_v3dNormalize(&temp);
            temp = math_v3dScale(&temp, cameraSpeed * SQRT_2);
            cam_AdjustPosition(Camera, -temp.x, -temp.y, -temp.z);

            //printf("W->");
            //math_v3dPrint(&temp);
        }
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_S))
        {
            temp = math_v3dCross(&Camera->m_MoveVector, &(TVector3d){0.0f, 1.0f, 0.0f});
            temp = math_v3dNormalize(&temp);
            temp = math_v3dScale(&temp, cameraSpeed * SQRT_2 );
            cam_AdjustPosition(Camera, temp.x, temp.y, temp.z);


            //printf("S->");
            //math_v3dPrint(&temp);
        }
        if(kb_GetKeyDown(keyboard, SDL_SCANCODE_SPACE))
        {
            temp = math_v3dScale(&Camera->m_Upward, cameraSpeed);
            cam_AdjustPosition(Camera, temp.x, temp.y, temp.z);
        }
        if(kb_GetKeyDown(keyboard, SDL_SCANCODE_LSHIFT))
        {
            temp = math_v3dScale(&Camera->m_Upward, cameraSpeed);
            cam_AdjustPosition(Camera, -temp.x, -temp.y, -temp.z);
        }
    }
    else if(Camera->m_IsMoveAlongAxis)
    {
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_W))
        {
            cam_AdjustPosition(Camera, 0, 0, cameraSpeed);
        }
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_S))
        {
            cam_AdjustPosition(Camera, 0, 0, -cameraSpeed);
        }
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_A))
        {
            cam_AdjustPosition(Camera, -cameraSpeed, 0, 0);
        }
        if (kb_GetKeyDown(keyboard, SDL_SCANCODE_D))
        {
            cam_AdjustPosition(Camera, cameraSpeed, 0, 0);
        }
        if(kb_GetKeyDown(keyboard, SDL_SCANCODE_SPACE))
        {
            cam_AdjustPosition(Camera, 0, cameraSpeed, 0);
        }
        if(kb_GetKeyDown(keyboard, SDL_SCANCODE_LSHIFT))
        {
            cam_AdjustPosition(Camera, 0, -cameraSpeed, 0);
        }
    }
    else if(Camera->m_IsCameraViewAround)
    {
        const float radius = 0.5f;
        static double time = 0;
        Camera->m_Position.x = sin( (time += 1.0f) / 400.0f ) * radius;
        Camera->m_Position.z = cos( (time += 1.0f) / 400.0f ) * radius;
        Camera->m_Position.y = 0.5f;
        TVector3d v1 = {0.0, 0.0, 0.0};

        cam_SetLookAtPosition(Camera, v1 );
        return;
    }
    /*
    else
    {
        if (kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_W))
        {
            temp = math_v3dScale(&Core->m_Camera.m_Frontward, cameraSpeed);
            cam_AdjustPosition(&Core->m_Camera, temp.x, temp.y, temp.z);
        }
        if (kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_S))
        {
            temp = math_v3dScale(&Core->m_Camera.m_Frontward, cameraSpeed);
            cam_AdjustPosition(&Core->m_Camera, -temp.x, -temp.y, -temp.z);

        }
        if (kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_A))
        {
            temp = math_v3dCross(&Core->m_Camera.m_Frontward, &Core->m_Camera.m_Upward);
            temp = math_v3dNormalize(&temp);
            temp = math_v3dScale(&temp, cameraSpeed);
            cam_AdjustPosition(&Core->m_Camera, -temp.x, -temp.y, -temp.z);

        }
        if (kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_D))
        {
            temp = math_v3dCross(&Core->m_Camera.m_Frontward, &Core->m_Camera.m_Upward);
            temp = math_v3dNormalize(&temp);
            temp = math_v3dScale(&temp, cameraSpeed);
            cam_AdjustPosition(&Core->m_Camera, temp.x, temp.y, temp.z);

        }
        if(kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_SPACE))
        {
            temp = math_v3dScale(&Core->m_Camera.m_Upward, cameraSpeed);
            cam_AdjustPosition(&Core->m_Camera, temp.x, temp.y, temp.z);
        }
        if(kb_GetKeyDown(&Core->m_Keyboard, SDL_SCANCODE_LSHIFT))
        {
            temp = math_v3dScale(&Core->m_Camera.m_Upward, cameraSpeed);
            cam_AdjustPosition(&Core->m_Camera, -temp.x, -temp.y, -temp.z);
        }
    }

    */
    cam_UpdateViewMatrix(Camera);


}




void cam_ResetProjection(TCamera* Camera)
{
    if(!Camera->m_IsOrthoProj)
    {
        cam_SetPerspective(Camera, 90.0f, Camera->m_AspectRatio, -50.0f, 50.0f);
    }
    else
    {
        float tmp = Camera->m_OrthoProjScale * Camera->m_AspectRatio;
        cam_SetOrtho(Camera, -Camera->m_OrthoProjScale, Camera->m_OrthoProjScale, - tmp , tmp, -50.0f, 50.0f);
    }
}

void cam_SetProjection(TCamera* Camera, float k)
{
    Camera->m_AspectRatio = k;
    if(!Camera->m_IsOrthoProj)
    {
        cam_SetPerspective(Camera, 90.0f, k, -5.0f, 10.0f);
    }
    else
    {
        float tmp = Camera->m_OrthoProjScale * k;
        printf("Projection parms: [%.4f] [%.4f] [%.4f] [%.4f]\n", - Camera->m_OrthoProjScale, Camera->m_OrthoProjScale, - tmp , tmp);
        cam_SetOrtho(Camera, - Camera->m_OrthoProjScale, Camera->m_OrthoProjScale, - tmp , tmp, -5.0f, 10.0f);
    }
}

void cam_SetLookAtPosition(TCamera* camera, TVector3d cameraTarget)
{
    TVector3d temp = math_v3dDifference(&camera->m_Position, &cameraTarget);
    TVector3d cameraDirection = math_v3dNormalize( &temp );

    TVector3d up = {0.0f, 1.0f, 0.0f};
    temp = math_v3dCross(&up, &cameraDirection);
    TVector3d cameraRight = math_v3dNormalize( &temp );

    TVector3d cameraUp = math_v3dCross(&cameraDirection, &cameraRight);

    if(camera->m_Position.x == cameraTarget.x &&
       camera->m_Position.y == cameraTarget.y &&
       camera->m_Position.z == cameraTarget.z)
    {
        //printf("Pos == Target");
        return;
    }

    matrixLookAt(camera->m_viewMatrix, &camera->m_Position, &cameraTarget, &cameraUp);
} // cam_SetLookAtPosition


void cam_SetLookDirect(TCamera* Camera, TRotation3d rot3)
{
    TVector3d direction;
    direction.x = cos(to_radians(rot3.yaw));
    direction.y = sin(to_radians(rot3.pitch));
    direction.z = sin(to_radians(rot3.yaw));


    Camera->m_Frontward = math_v3dNormalize(&direction);


    cam_UpdateViewMatrix(Camera);
}



void cam_ResetRotation(TCamera* Camera)
{
    Camera->m_Rotation.yaw = -90.0f;
    Camera->m_Rotation.pitch = 0;
    Camera->m_Rotation.roll = 0;

    cam_UpdateViewMatrix(Camera);
}

void cam_ResetPosition(TCamera* camera)
{
    camera->m_Position.x = 0;
    camera->m_Position.y = 0;
    camera->m_Position.z = 3.0f;

    cam_UpdateViewMatrix(camera);
}

void cam_ResetPositionRotation(TCamera* Camera)
{
    Camera->m_Position  = math_Vector3d(0.0f, 0.0f, 3.0f);
    Camera->m_Frontward = math_Vector3d(0.0f, 0.0f, -1.0f);
    Camera->m_Upward    = math_Vector3d(0.0f, 1.0f, 0.0f);
    Camera->m_Rotation  = (TRotation3d){-90.0f, 0.0f, 0.0f};


    Camera->m_OrthoProjScale = 1.0f;

    cam_UpdateViewMatrix(Camera);
}

void cam_SetOrtho(TCamera* camera, float bottom, float top, float left, float right, float zNear, float zFar)
{
    matrixOrtho(camera->m_projectionMatrix, bottom, top, left, right, zNear, zFar);
}

void cam_SetPerspective(TCamera* camera, float fieldOfView, float aspectRatio, float zNear, float zFar)
{
    matrixPerspective(camera->m_projectionMatrix, fieldOfView, aspectRatio, zNear, zFar);
}


void cam_AdjustPosition(TCamera* camera, float x, float y, float z)
{
    camera->m_Position.x += x;
    camera->m_Position.y += y;
    camera->m_Position.z += z;
}
/*
void cam_AdjustRotationX(TCamera* camera, float x)
{
    camera->m_Rotation.x += x;
}

void cam_AdjustRotationY(TCamera* camera, float y)
{
    camera->m_Rotation.y += y;
}
void cam_AdjustRotationZ(TCamera* camera, float z)
{
    camera->m_Rotation.z += z;
}
*/

void cam_SetPosition(TCamera* camera, float x, float y, float z)
{
    camera->m_Position.x = x;
    camera->m_Position.y = y;
    camera->m_Position.z = z;
}
/*
void cam_SetRotation(TCamera* camera, float x, float y, float z)
{
    camera->m_Rotation.x = x;
    camera->m_Rotation.y = y;
    camera->m_Rotation.z = z;
}
*/

void cam_UpdateViewMatrix(TCamera* camera)
{
    loadIdentity(camera->m_viewMatrix);


    TVector3d temp = {camera->m_Position.x + camera->m_Frontward.x,
                      camera->m_Position.y + camera->m_Frontward.y,
                      camera->m_Position.z + camera->m_Frontward.z};


    matrixLookAt(camera->m_viewMatrix, &camera->m_Position, &temp, &camera->m_Upward );
}

void cam_Info(TCamera* camera)
{
    printf("Cam Pos: %.2f %.2f %.2f\n", camera->m_Position.x, camera->m_Position.y, camera->m_Position.z);

}
