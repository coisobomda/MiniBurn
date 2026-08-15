#include "texture.h"
#include "mesh.h"
#include <glad/glad.h>
#include "stb_image.h"


GLuint loadTexture(const char* path) {
    GLuint texture;
    int width, height, channels;

    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        printf("Falhou ao carregar %s\n", path);
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format;

    if (channels == 4)
        format = GL_RGBA;
    else
        format = GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    return texture;
}

GLuint bindTexture(GLuint texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
}


