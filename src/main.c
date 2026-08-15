#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "render.h"
#include "mesh.h"
#include "math/vector.h"
#include "texture.h"

int running = 1;


float vertices[] = {
    // Frente (+Z)
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,

    // Trás (-Z)
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f,

    // Esquerda (-X)
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,

    // Direita (+X)
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f,

    // Topo (+Y)
    -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,

    // Base (-Y)
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 1.0f
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
    windowInit();
    compileShaders();
    Object cube, cube2;

    // cria mesh
    Mesh cubemesh = createMesh(vertices, sizeof(vertices), indices, sizeof(indices));
    // cria transform
    Transform transform = createTransform();
    Transform transform2 = createTransform();
    transform.scale = (vec3){1.0f, 1.0f, 1.0f};
    transform.position = (vec3){0.0f, 0.0f, 0.0f};
    transform.rotation = (vec3){0.0f, 0.0f, 0.0f};


    GLuint texture = loadTexture("src/missing.png");

    cube = createObject(cubemesh, transform, texture);




    SDL_Event event;

    while (running) {

        render(cube);
        cube.transform.position.z += -0.01;
        printf("%f\n", cube.transform.position.z);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

        }
    }
    endProgram();
}
