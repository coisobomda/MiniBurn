#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "render.h"
#include "mesh.h"
#include "mat4.h"

int running = 1;

mat4 matrixA = {{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
}};

mat4 matrixB = {{
    {17, 18, 19, 20},
    {21, 22, 23, 24},
    {25, 26, 27, 28},
    {29, 30, 31, 32}
}};

float vertices[] = {
    // Frente (+Z)
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    // Trás (-Z)
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

    // Esquerda (-X)
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

    // Direita (+X)
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,

    // Topo (+Y)
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    // Base (-Y)
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f
};

unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,        // Frente
    4, 5, 6, 6, 7, 4,        // Trás
    8, 9,10,10,11, 8,        // Esquerda
   12,13,14,14,15,12,        // Direita
   16,17,18,18,19,16,        // Topo
   20,21,22,22,23,20         // Base
};

int main(void) {
    mat4 result = multiplyMat4(matrixA, matrixB);
    printMat4(result);
    windowInit();
    compileShaders();

    Mesh cubemesh = createMesh(vertices, sizeof(vertices), indices, sizeof(indices));
    Transform transform;
    Object cube = createObject(cubemesh, transform);

    SDL_Event event;

    while (running) {
        render(cube);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

        }
    }
    endProgram();
}
