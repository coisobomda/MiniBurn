#include "math/vector.h"
#include "math/mat4.h"
#include "math/normalize.h"
#include "camera.h"
#include <math.h>
#include <stdio.h>
#include "math/radians.h"

mat4 generateViewMatrix(Camera camera) {
    float yaw = toRadians(camera.yaw);
    float pitch = toRadians(camera.pitch);

    camera.direction.x = sinf(yaw) * cosf(pitch);
    camera.direction.y = sinf(pitch);
    camera.direction.z = -cosf(yaw) * cosf(pitch);
    camera.direction = normalize(camera.direction);

    vec3 up = (vec3){0.0f, 1.0f, 0.0f};
    camera.right = normalize(cross(up, camera.direction));

    camera.up = cross(camera.direction, camera.right);

    mat4 lookAt = {0};
    lookAt = identity(lookAt);

    lookAt.m[3][0] = -dot(camera.right, camera.position);
    lookAt.m[3][1] = -dot(camera.up, camera.position);
    lookAt.m[3][2] = -dot(camera.direction, camera.position);

    lookAt.m[0][0] = camera.right.x;
    lookAt.m[1][0] = camera.right.y;
    lookAt.m[2][0] = camera.right.z;
    lookAt.m[0][1] = camera.up.x;
    lookAt.m[1][1] = camera.up.y;
    lookAt.m[2][1] = camera.up.z;
    lookAt.m[0][2] = camera.direction.x;
    lookAt.m[1][2] = camera.direction.y;
    lookAt.m[2][2] = camera.direction.z;

    return lookAt;

}

mat4 perspective(float fov, float aspect, float near, float far) {
    mat4 P = {0};
    float f = 1.0f / tanf(fov / 2.0f);

    P.m[0][0] = f / aspect;
    P.m[0][1] = 0;
    P.m[0][2] = 0;
    P.m[0][3] = 0;

    P.m[1][0] = 0;
    P.m[1][1] = f;
    P.m[1][2] = 0;
    P.m[1][3] = 0;

    P.m[2][0] = 0;
    P.m[2][1] = 0;
    P.m[2][2] = (far + near) / (near - far);
    P.m[2][3] = -1;

    P.m[3][0] = 0;
    P.m[3][1] = 0;
    P.m[3][2] = (2 * far * near) / (near - far);
    P.m[3][3] = 0;

    return P;
}
