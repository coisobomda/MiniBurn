#ifndef MAT4_H
#define MAT4_H

typedef struct{
    float m[4][4];
} mat4;

mat4 multiplyMat4(mat4 matrixA, mat4 matrixB);
void printMat4(mat4 matrix);
mat4 identity(mat4 matrix);

#endif
