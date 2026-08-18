#include "mat4.h"
#include <stdio.h>

mat4 multiplyMat4(mat4 matrixA, mat4 matrixB) {
    mat4 result;

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            result.m[row][column] = 0.0f;

            for (int index = 0; index < 4; index++)
            {
                result.m[row][column] +=
                    matrixA.m[row][index] *
                    matrixB.m[index][column];
            }
        }
    }

    return result;
}

void printMat4(mat4 matrix) {
    for (int row = 0; row < 4; row++)
    {
        printf("| ");

        for (int column = 0; column < 4; column++)
        {
            printf("%.1f ", matrix.m[row][column]);
        }

        printf("|\n");
    }
}

mat4 identity(mat4 matrix) {
    mat4 matrixResult = matrix;
    matrixResult.m[0][0] = 1.0f;
    matrixResult.m[1][1] = 1.0f;
    matrixResult.m[2][2] = 1.0f;
    matrixResult.m[3][3] = 1.0f;

    return matrixResult;
}


