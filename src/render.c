#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include "math/mat4.h"
#include "math/radians.h"
#include "mesh.h"
#include <math.h>
#include "texture.h"
#include "camera.h"

SDL_Window *window;
SDL_GLContext context;

GLuint shaderProgram, vertexShader, fragmentShader;

int WIDTH = 1280;
int HEIGHT = 720;
mat4 projection;

void windowInit(void) {
    SDL_Init(SDL_INIT_VIDEO);
    
    // window
    window = SDL_CreateWindow("MiniBurn", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to load OpenGL\n");
    }
}

char* readShaderFile(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error: %s\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}


void compileShaders() {
    // load shader files
    const char* vertexShaderSource = readShaderFile("src/shader/default.vert");

    const char* fragmentShaderSource = readShaderFile("src/shader/default.frag");

    // vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    shaderProgram = glCreateProgram();

    // attach shader
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glEnable(GL_DEPTH_TEST);

    projection = perspective(toRadians(90.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    printMat4(projection);
    
}



void render(Object object, Camera camera) {
    mat4 matrixScale = {0};
    mat4 matrixTranslation = {0};

    mat4 matrixRotationZ = {0};
    mat4 matrixRotationY = {0};
    mat4 matrixRotationX = {0};

    mat4 matrixRotation = {0};

    mat4 matrix = {0};

    // scale matrix
    matrixScale.m[0][0] = object.transform.scale.x;
    matrixScale.m[1][1] = object.transform.scale.y;
    matrixScale.m[2][2] = object.transform.scale.z;
    matrixScale.m[3][3] = 1.0f;

    // convert rotation in dregrees to radians
    float angleZ = toRadians(object.transform.rotation.z);
    float angleY = toRadians(object.transform.rotation.y);
    float angleX = toRadians(object.transform.rotation.x);

    // calculates sine and cossine
    float cZ = cos(angleZ);
    float sZ = sin(angleZ);

    float cY = cos(angleY);
    float sY = sin(angleY);

    float cX = cos(angleX);
    float sX = sin(angleX);

    // creates Z rotation matrix
    matrixRotationZ.m[0][0] = cZ;
    matrixRotationZ.m[0][1] = -sZ;
    matrixRotationZ.m[1][0] = sZ;
    matrixRotationZ.m[1][1] = cZ;
    matrixRotationZ.m[2][2] = 1.0f;
    matrixRotationZ.m[3][3] = 1.0f;

    // creates Y rotation matrix
    matrixRotationY.m[0][0] = cY;
    matrixRotationY.m[0][2] = sY;
    matrixRotationY.m[2][0] = -sY;
    matrixRotationY.m[2][2] = cY;
    matrixRotationY.m[1][1] = 1.0f;
    matrixRotationY.m[3][3] = 1.0f;

    // creates X rotation matrix
    matrixRotationX.m[1][1] = cX;
    matrixRotationX.m[1][2] = -sX;
    matrixRotationX.m[2][1] = sX;
    matrixRotationX.m[2][2] = cX;
    matrixRotationX.m[0][0] = 1.0f;
    matrixRotationX.m[3][3] = 1.0f;

    // creates rotation matrix
    matrixRotation = multiplyMat4(matrixRotationZ, matrixRotationY);
    matrixRotation = multiplyMat4(matrixRotation, matrixRotationX);

    // translation
    matrixTranslation.m[3][0] = object.transform.position.x;
    matrixTranslation.m[3][1] = object.transform.position.y;
    matrixTranslation.m[3][2] = object.transform.position.z;
    matrixTranslation.m[0][0] = 1.0f;
    matrixTranslation.m[1][1] = 1.0f;
    matrixTranslation.m[2][2] = 1.0f;
    matrixTranslation.m[3][3] = 1.0f;
    matrix = multiplyMat4(matrixScale, matrixTranslation);
    matrix = multiplyMat4(matrix, matrixRotation);

    // main rendering
    glUseProgram(shaderProgram);

    GLint transformLocation = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &matrix.m[0][0]);

    glActiveTexture(GL_TEXTURE0);
    bindTexture(object.texture);

    GLint textureLocation = glGetUniformLocation(shaderProgram, "ourTexture");
    glUniform1i(textureLocation, 0);

    GLint viewLocation = glGetUniformLocation(shaderProgram, "view");
    mat4 viewMatrix = generateViewMatrix(camera);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix.m[0][0]);

    GLint perspectiveLocation = glGetUniformLocation(shaderProgram, "perspective");
    glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, &projection.m[0][0]);

    glBindVertexArray(object.mesh.VAO);
    glDrawElements(GL_TRIANGLES, object.mesh.indexCount, GL_UNSIGNED_INT, 0);

}

void endProgram() {
    glDeleteProgram(shaderProgram);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clear() {
    glClearColor(0.11f, 0.14f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swap() {
    SDL_GL_SwapWindow(window);
    glBindVertexArray(0);
}

