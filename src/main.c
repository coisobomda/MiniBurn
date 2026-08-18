#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "render.h"
#include "mesh.h"
#include "math/vector.h"
#include "texture.h"
#include "camera.h"
#include <math.h>

int running = 1;
float deltaTime;


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
    GLuint texture2 = loadTexture("src/tung.jpg");
    Camera camera = {};
    camera.position = (vec3){0.0f, 0.0f, -5.0f};

    cube = createObject(cubemesh, transform, texture2);
    cube2 = createObject(cubemesh, transform, texture);




    SDL_Event event;
    cube.transform.position.z = 0.0f;
    cube2.transform.position.x = 2.0f;

    while (running) {
        clear();
        deltaTime = SDL_GetTicks64() / 1000.0f;

        // float camX = sin(1 * deltaTime) * 5;
        // float camZ = cos(1 * deltaTime) * 5;

        // camera.position = (vec3){camX, 0, camZ};

        render(cube, camera);
        render(cube2, camera);
        cube.transform.rotation.z += -1.0f;
        swap();

        const Uint8* keyboard = SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                // Exit or close menu
                    break;
                case SDLK_w:
                    camera.position.z += 0.1f;
                    break;
                case SDLK_s:
                    camera.position.z -= 0.1f;
                    break;
                case SDLK_a:
                    camera.position.x += 0.1f;
                    break;
                case SDLK_d:
                    camera.position.x -= 0.1f;
                    break;
                case SDLK_e:
                    camera.yaw += 5;
                    break;
                case SDLK_q:
                    camera.yaw -= 5;
                    break;
                case SDLK_i:
                    camera.pitch += 5;
                    break;
                case SDLK_j:
                    camera.pitch -= 5;
                    break;

                }
            }

        }
    }
    endProgram();
}
