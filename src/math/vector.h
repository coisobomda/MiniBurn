#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
    float z;
} vec3;

static vec3 vectorSub(vec3 a, vec3 b) {
    return (vec3){
    a.x - b.x,
    a.y - b.y,
    a.z - b.z
    };
}
static float dot(vec3 a, vec3 b) {
    return a.x * b.x +
           a.y * b.y +
           a.z * b.z;
}

#endif
