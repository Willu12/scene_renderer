#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct SceneConfiguration {
    float* controlPoints;
    int tesselationLevel;
    bool day;
    bool fog;
    float fogIntensity;
    float kaDay;
    float kaNight;
    float ks;
    float kd;
    int m;
    int k;
};