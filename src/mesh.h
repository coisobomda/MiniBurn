#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include "math/vector.h"

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

typedef struct {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    unsigned int indexCount;
    unsigned int vertexSize;
} Mesh;

typedef struct {
    Mesh mesh;
    Transform transform;
    GLuint texture;
} Object;

Object createObject(Mesh mesh, Transform transform, GLuint texture);
Mesh createMesh(float* vertices, unsigned int vertexSize, unsigned int* indices, unsigned int indexSize);
Transform createTransform();

#endif
