#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>

void windowInit(void);

int render(float vertices[], size_t sizeVert, GLuint indices[], size_t sizeInd);
void endProgram();

#endif
