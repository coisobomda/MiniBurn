#include "mesh.h"
#include "math/vector.h"
#include <glad/glad.h>
#include <stdio.h>

Object createObject(Mesh mesh, Transform transform, GLuint texture) {
    Object object;
    object.mesh = mesh;
    object.transform = transform;
    object.texture = texture;

    return object;
}

Mesh createMesh(float* vertices, unsigned int vertexSize, unsigned int* indices, unsigned int indexSize) {

    Mesh mesh;
    GLuint VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO); 

    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mesh.VAO = VAO;
    mesh.VBO = VBO;
    mesh.EBO = EBO;

    mesh.indexCount = indexSize / sizeof(unsigned int);
    mesh.vertexSize = vertexSize;

    return mesh;
}

Transform createTransform() {
    Transform transform;

    transform.position = (vec3){0.0f, 0.0f, 0.0f};
    transform.rotation = (vec3){0.0f, 0.0f, 0.0f};
    transform.scale = (vec3){1.0f, 1.0f, 1.0f};

    return transform;
}
