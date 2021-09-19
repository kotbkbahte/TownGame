#include "Matrix.h"

#define M_PI 3.14159265358979323846

void matrixLookAt(float* matrix, TVector3d* Eye, TVector3d* Center, TVector3d* Up)
{
    TVector3d X, Y, Z;

    Z = math_v3dDifference(Eye, Center);
    Z = math_v3dNormalize(&Z);

    Y = *Up;
    X = math_v3dCross(&Y, &Z);

    Y = math_v3dCross(&Z, &X);

    X = math_v3dNormalize(&X);
    Y = math_v3dNormalize(&Y);

    matrix[0] = X.x;
    matrix[4] = X.y;
    matrix[8] = X.z;
    matrix[12] = - math_v3dDot(&X, Eye);

    matrix[1] = Y.x;
    matrix[5] = Y.y;
    matrix[9] = Y.z;
    matrix[13] = - math_v3dDot(&Y, Eye);

    matrix[2]  = Z.x;
    matrix[6]  = Z.y;
    matrix[10] = Z.z;
    matrix[14] = - math_v3dDot(&Z, Eye);

    matrix[3] = 0;
    matrix[7] = 0;
    matrix[11] = 0;
    matrix[15] = 1.0f;

    //Matrix[0][0] = X.x;
    //Matrix[1][0] = X.y;
    //Matrix[2][0] = X.z;
    //Matrix[3][0] = -X.Dot( Eye );
    //Matrix[0][1] = Y.x;
    //Matrix[1][1] = Y.y;
    //Matrix[2][1] = Y.z;
    //Matrix[3][1] = -Y.Dot( Eye );
    //Matrix[0][2] = Z.x;
    //Matrix[1][2] = Z.y;
    //Matrix[2][2] = Z.z;
    //Matrix[3][2] = -Z.Dot( Eye );
    //Matrix[0][3] = 0;
    //Matrix[1][3] = 0;
    //Matrix[2][3] = 0;
    //Matrix[3][3] = 1.0f;
    return;
}




void matrixScale(float* matrix, float x, float y, float z)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[0] = x;
    tempMatrix[5] = y;
    tempMatrix[10] = z;
    multiplyMatrix(matrix, tempMatrix, matrix);
}

void matrixFrustum(float* matrix, float left, float right, float bottom, float top, float zNear, float zFar)
{
    float temp, xDistance, yDistance, zDistance;
    temp = 2.0 *zNear;
    xDistance = right - left;
    yDistance = top - bottom;
    zDistance = zFar - zNear;
    loadIdentity(matrix);
    matrix[0] = temp / xDistance;
    matrix[5] = temp / yDistance;


    matrix[6] = (top + bottom) / yDistance;
    matrix[8] = (right + left) / xDistance;
    matrix[10] = (-zFar - zNear) / zDistance;
    matrix[14] = -1.0f;
    matrix[11] = (-temp * zFar) / zDistance;
    matrix[15] = 0.0f;
}

void matrixOrtho(float* matrix, float bottom, float top, float left, float right, float zNear, float zFar)
{
    loadIdentity(matrix);
    matrix[0] = 2 / (right - left);
    matrix[5] = 2 / (top - bottom);
    matrix[10] = -2 / (zFar - zNear);
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(zFar + zNear) / (zFar - zNear);
    matrix[15] = 1;
}

void matrixPerspective(float* matrix, float fieldOfView, float aspectRatio, float zNear, float zFar)
{
    float ymax, xmax;
    ymax = zNear * tanf(fieldOfView * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    matrixFrustum(matrix, -xmax, xmax, -ymax, ymax, zNear, zFar);
}

void matrixTranslate(float* matrix, float x, float y, float z)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[12] = x;
    tempMatrix[13] = y;
    tempMatrix[14] = z;
    multiplyMatrix(matrix, tempMatrix, matrix);
}

void matrixRotateZ(float *matrix, float angle)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[0] = cos(to_radians(angle));
    tempMatrix[4] = -sin(to_radians(angle));
    tempMatrix[1] = sin(to_radians(angle));
    tempMatrix[5] = cos(to_radians(angle));
    multiplyMatrix(matrix, tempMatrix, matrix);
}

void matrixRotateY(float *matrix, float angle)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[0] = cos(to_radians(angle));
    tempMatrix[2] = sin(to_radians(angle));
    tempMatrix[8] = -sin(to_radians(angle));
    tempMatrix[10] = cos(to_radians(angle));
    multiplyMatrix(matrix, tempMatrix, matrix);
}

void matrixRotateX(float *matrix, float angle)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[5] = cos(to_radians(angle));
    tempMatrix[6] = -sin(to_radians(angle));
    tempMatrix[9] = sin(to_radians(angle));
    tempMatrix[10] = cos(to_radians(angle));
    multiplyMatrix(matrix, tempMatrix, matrix);
}


float to_radians(float degrees)
{
    return M_PI * degrees / 180.0f;
}

void loadIdentity(float* matrix)
{
    if(matrix == NULL)
    {
        return;
    }
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void multiplyMatrix(float* destination, float* operand1, float* operand2)
{
    float theResult[16];
    int i,j = 0;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            theResult[4 * i + j] = operand1[j] * operand2[4 * i] + operand1[4 + j] * operand2[4 * i + 1] +
                                   operand1[8 + j] * operand2[4 * i + 2] + operand1[12 + j] * operand2[4 * i + 3];
        }
    }
    for(int i = 0; i < 16; i++)
    {
        destination[i] = theResult[i];
    }
}

int copyMatrix_fd(float* src, double* dest)
{
    if( (src == NULL) || (dest == NULL) )
        return -1;

    for (int i = 0; i < 16; i++)
    {
        dest[i] = (double)src[i];
    }
    return 1;

}

void printMatrix(float* mat)
{
    printf("#\n");
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%.2f\t", mat[4* i + j]);
        }
        printf("\n");
    }
    printf("#\n");
}

void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2)
{
    result[0]=matrix1[0]*matrix2[0]+
      matrix1[4]*matrix2[1]+
      matrix1[8]*matrix2[2]+
      matrix1[12]*matrix2[3];
    result[4]=matrix1[0]*matrix2[4]+
      matrix1[8]*matrix2[6]+
      matrix1[4]*matrix2[5]+
      matrix1[12]*matrix2[7];
    result[8]=matrix1[0]*matrix2[8]+
      matrix1[4]*matrix2[9]+
      matrix1[8]*matrix2[10]+
      matrix1[12]*matrix2[11];
    result[12]=matrix1[0]*matrix2[12]+
      matrix1[4]*matrix2[13]+
      matrix1[8]*matrix2[14]+
      matrix1[12]*matrix2[15];
    result[1]=matrix1[1]*matrix2[0]+
      matrix1[5]*matrix2[1]+
      matrix1[9]*matrix2[2]+
      matrix1[13]*matrix2[3];
    result[5]=matrix1[1]*matrix2[4]+
      matrix1[5]*matrix2[5]+
      matrix1[9]*matrix2[6]+
      matrix1[13]*matrix2[7];
    result[9]=matrix1[1]*matrix2[8]+
      matrix1[5]*matrix2[9]+
      matrix1[9]*matrix2[10]+
      matrix1[13]*matrix2[11];
    result[13]=matrix1[1]*matrix2[12]+
      matrix1[5]*matrix2[13]+
      matrix1[9]*matrix2[14]+
      matrix1[13]*matrix2[15];
    result[2]=matrix1[2]*matrix2[0]+
      matrix1[6]*matrix2[1]+
      matrix1[10]*matrix2[2]+
      matrix1[14]*matrix2[3];
    result[6]=matrix1[2]*matrix2[4]+
      matrix1[6]*matrix2[5]+
      matrix1[10]*matrix2[6]+
      matrix1[14]*matrix2[7];
    result[10]=matrix1[2]*matrix2[8]+
      matrix1[6]*matrix2[9]+
      matrix1[10]*matrix2[10]+
      matrix1[14]*matrix2[11];
    result[14]=matrix1[2]*matrix2[12]+
      matrix1[6]*matrix2[13]+
      matrix1[10]*matrix2[14]+
      matrix1[14]*matrix2[15];
    result[3]=matrix1[3]*matrix2[0]+
      matrix1[7]*matrix2[1]+
      matrix1[11]*matrix2[2]+
      matrix1[15]*matrix2[3];
    result[7]=matrix1[3]*matrix2[4]+
      matrix1[7]*matrix2[5]+
      matrix1[11]*matrix2[6]+
      matrix1[15]*matrix2[7];
    result[11]=matrix1[3]*matrix2[8]+
      matrix1[7]*matrix2[9]+
      matrix1[11]*matrix2[10]+
      matrix1[15]*matrix2[11];
    result[15]=matrix1[3]*matrix2[12]+
      matrix1[7]*matrix2[13]+
      matrix1[11]*matrix2[14]+
      matrix1[15]*matrix2[15];
}


int glhUnProjectf(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate)
  {
      // Transformation matrices
      float m[16], A[16];
      float in[4], out[4];
      // Calculation for inverting a matrix, compute projection x modelview
      // and store in A[16]
      MultiplyMatrices4by4OpenGL_FLOAT(A, projection, modelview);
      // Now compute the inverse of matrix A
      if(glhInvertMatrixf2(A, m)==0)
         return 0;
      // Transformation of normalized coordinates between -1 and 1
      in[0]=(winx-(float)viewport[0])/(float)viewport[2]*2.0-1.0;
      in[1]=(winy-(float)viewport[1])/(float)viewport[3]*2.0-1.0;
      in[2]=2.0*winz-1.0;
      in[3]=1.0;
      // Objects coordinates
      MultiplyMatrixByVector4by4OpenGL_FLOAT(out, m, in);
      if(out[3]==0.0)
         return 0;
      out[3]=1.0/out[3];
      objectCoordinate[0]=out[0]*out[3];
      objectCoordinate[1]=out[1]*out[3];
      objectCoordinate[2]=out[2]*out[3];
      return 1;
  }


  void MultiplyMatrixByVector4by4OpenGL_FLOAT(float *resultvector, const float *matrix, const float *pvector)
  {
    resultvector[0]=matrix[0]*pvector[0]+matrix[4]*pvector[1]+matrix[8]*pvector[2]+matrix[12]*pvector[3];
    resultvector[1]=matrix[1]*pvector[0]+matrix[5]*pvector[1]+matrix[9]*pvector[2]+matrix[13]*pvector[3];
    resultvector[2]=matrix[2]*pvector[0]+matrix[6]*pvector[1]+matrix[10]*pvector[2]+matrix[14]*pvector[3];
    resultvector[3]=matrix[3]*pvector[0]+matrix[7]*pvector[1]+matrix[11]*pvector[2]+matrix[15]*pvector[3];
  }

  #define SWAP_ROWS_DOUBLE(a, b) { double *_tmp = a; (a)=(b); (b)=_tmp; }
  #define SWAP_ROWS_FLOAT(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
  #define MAT(m,r,c) (m)[(c)*4+(r)]

  // This code comes directly from GLU except that it is for float
int glhInvertMatrixf2(float *m, float *out)
{
   float wtmp[4][8];
   float m0, m1, m2, m3, s;
   float *r0, *r1, *r2, *r3;
   r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
   r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1),
      r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3),
      r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
      r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1),
      r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3),
      r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
      r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),
      r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),
      r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
      r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),
      r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),
      r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
   /* choose pivot - or die */
   if (fabsf(r3[0]) > fabsf(r2[0]))
      SWAP_ROWS_FLOAT(r3, r2);
   if (fabsf(r2[0]) > fabsf(r1[0]))
      SWAP_ROWS_FLOAT(r2, r1);
   if (fabsf(r1[0]) > fabsf(r0[0]))
      SWAP_ROWS_FLOAT(r1, r0);
   if (0.0 == r0[0])
      return 0;
   /* eliminate first variable */
   m1 = r1[0] / r0[0];
   m2 = r2[0] / r0[0];
   m3 = r3[0] / r0[0];
   s = r0[1];
   r1[1] -= m1 * s;
   r2[1] -= m2 * s;
   r3[1] -= m3 * s;
   s = r0[2];
   r1[2] -= m1 * s;
   r2[2] -= m2 * s;
   r3[2] -= m3 * s;
   s = r0[3];
   r1[3] -= m1 * s;
   r2[3] -= m2 * s;
   r3[3] -= m3 * s;
   s = r0[4];
   if (s != 0.0) {
      r1[4] -= m1 * s;
      r2[4] -= m2 * s;
      r3[4] -= m3 * s;
   }
   s = r0[5];
   if (s != 0.0) {
      r1[5] -= m1 * s;
      r2[5] -= m2 * s;
      r3[5] -= m3 * s;
   }
   s = r0[6];
   if (s != 0.0) {
      r1[6] -= m1 * s;
      r2[6] -= m2 * s;
      r3[6] -= m3 * s;
   }
   s = r0[7];
   if (s != 0.0) {
      r1[7] -= m1 * s;
      r2[7] -= m2 * s;
      r3[7] -= m3 * s;
   }
   /* choose pivot - or die */
   if (fabsf(r3[1]) > fabsf(r2[1]))
      SWAP_ROWS_FLOAT(r3, r2);
   if (fabsf(r2[1]) > fabsf(r1[1]))
      SWAP_ROWS_FLOAT(r2, r1);
   if (0.0 == r1[1])
      return 0;
   /* eliminate second variable */
   m2 = r2[1] / r1[1];
   m3 = r3[1] / r1[1];
   r2[2] -= m2 * r1[2];
   r3[2] -= m3 * r1[2];
   r2[3] -= m2 * r1[3];
   r3[3] -= m3 * r1[3];
   s = r1[4];
   if (0.0 != s) {
      r2[4] -= m2 * s;
      r3[4] -= m3 * s;
   }
   s = r1[5];
   if (0.0 != s) {
      r2[5] -= m2 * s;
      r3[5] -= m3 * s;
   }
   s = r1[6];
   if (0.0 != s) {
      r2[6] -= m2 * s;
      r3[6] -= m3 * s;
   }
   s = r1[7];
   if (0.0 != s) {
      r2[7] -= m2 * s;
      r3[7] -= m3 * s;
   }
   /* choose pivot - or die */
   if (fabsf(r3[2]) > fabsf(r2[2]))
      SWAP_ROWS_FLOAT(r3, r2);
   if (0.0 == r2[2])
      return 0;
   /* eliminate third variable */
   m3 = r3[2] / r2[2];
   r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
      r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];
   /* last check */
   if (0.0 == r3[3])
      return 0;
   s = 1.0 / r3[3];		/* now back substitute row 3 */
   r3[4] *= s;
   r3[5] *= s;
   r3[6] *= s;
   r3[7] *= s;
   m2 = r2[3];			/* now back substitute row 2 */
   s = 1.0 / r2[2];
   r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
      r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
   m1 = r1[3];
   r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
      r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
   m0 = r0[3];
   r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
      r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
   m1 = r1[2];			/* now back substitute row 1 */
   s = 1.0 / r1[1];
   r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
      r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
   m0 = r0[2];
   r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
      r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
   m0 = r0[1];			/* now back substitute row 0 */
   s = 1.0 / r0[0];
   r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
      r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
   MAT(out, 0, 0) = r0[4];
   MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
   MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
   MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
   MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
   MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
   MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
   MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
   MAT(out, 3, 3) = r3[7];


   return 1;
}
