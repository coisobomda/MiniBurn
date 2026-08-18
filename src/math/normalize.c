#include "vector.h"
#include "math.h"

vec3 normalize(vec3 v){
    float lenght = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    
    if (lenght == 0.0f) {
        return (vec3){0.0f, 0.0f, 0.0f};
    }

    return (vec3){
        v.x / lenght,
        v.y / lenght,
        v.z / lenght
    };
}

vec3 cross(vec3 a, vec3 b) {
    return (vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
