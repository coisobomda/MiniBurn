#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "mesh.h"

void windowInit(void);
int compileShaders();
int render(Object object);
void endProgram();

#endif
