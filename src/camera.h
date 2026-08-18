#ifndef CAMERA_H
#define CAMERA_H

#include "math/vector.h"
#include "math/mat4.h"

typedef struct {
    vec3 position;
    vec3 direction;
    vec3 right;
    vec3 up;

    int yaw;
    int pitch;
    
} Camera;

mat4 generateViewMatrix(Camera camera);
mat4 perspective(float fov, float aspect, float near, float far);

#endif
