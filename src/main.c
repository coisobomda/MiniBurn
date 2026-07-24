#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "render.h"

int running = 1;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

int main(void) {
    windowInit();

    SDL_Event event;

    while (running) {
        render(vertices, sizeof(vertices), indices, sizeof(indices));
        printf("loop");
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

        }
    }
    endProgram();
}
