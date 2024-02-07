#pragma once

#include "animated_object.hpp"
#include "model.hpp"


class CatBus : public AnimatedObject {
public:
    CatBus(const glm::vec3& center, float r);
private:
    const float scale = 0.1f;
};