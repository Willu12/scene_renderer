#pragma once

#include "model.hpp"

class StaticObject {
public:
    StaticObject(Model &model);
    StaticObject(const std::string& path);
    virtual void Draw(Shader& shader, const Camera& camera);

    Model* model;
};
