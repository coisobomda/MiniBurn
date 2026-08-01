#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include "vector.h"

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

typedef struct {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
} Mesh;

typedef struct {
    Mesh mesh;
    Transform transform;
} Object;

Object createObject(Mesh mesh, Transform transform);
Mesh createMesh(float* vertices, unsigned int vertexSize, unsigned int* indices, unsigned int indexSize);
Transform createTransform();

#endif
