#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "mesh.h"

GLuint loadTexture(const char* path);
GLuint bindTexture(GLuint texture);


#endif
