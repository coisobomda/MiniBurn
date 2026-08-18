#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include "camera.h"
#include "mesh.h"


void windowInit(void);
int compileShaders();
int render(Object object, Camera camera);
void endProgram();
void clear();
void swap();

#endif
