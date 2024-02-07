#pragma once

#include "static_object.hpp"

class AnimatedObject : public StaticObject {
public:
    AnimatedObject(Model &model, const glm::vec3& center, float r);
    AnimatedObject(const std::string& path, const glm::vec3& center, float r);
    void move_object();
    void update_model_matrix(const glm::mat4& model_matrix);
    void Draw(Shader& shader, const Camera& camera) override;
    glm::vec3 GetPosition() const;
    glm::vec3 GetFrontVector() const;
private:
    const float scale = 0.01f;
    glm::vec3 position;
    glm::vec3 center;
    float angle, r;
};
