#include "include/animated_object.hpp"

AnimatedObject::AnimatedObject(Model &model, const glm::vec3& center, float r) : StaticObject(model) {
    this->angle = 0.0f;
    this->center = center;
    this->r = r;
    this->position = glm::vec3(center.x + r, center.y, center.z);
}

void AnimatedObject::update_model_matrix(const glm::mat4 &model_matrix) {
    model->model_matrix = model_matrix;
}

void AnimatedObject::move_object() {
    const float deltaAnglePerSecond = 0.3f;

    angle +=  deltaAnglePerSecond;
    if(angle > 360.0f)
        angle = angle - 360.0f;
    position.x = cos(glm::radians(angle)) * r;
    position.y = sin(glm::radians(angle)) * r;
    //update_pov_camera();
}

void AnimatedObject::Draw(Shader &shader, const Camera &camera) {

    glm::mat4 mm(1.0f);
    mm = glm::translate(mm, position);
    mm = glm::rotate(mm,1.5f,glm::vec3(1.0,0.0,0.0));// translate it down so it's at the center of the scene
    mm = glm::rotate(mm, glm::radians(angle + 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mm = glm::scale(mm, glm::vec3(scale, scale, scale));
    this->update_model_matrix(mm);
    StaticObject::Draw(shader,camera);

    this->move_object();
}

glm::vec3 AnimatedObject::GetPosition() const {
    return position + glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 AnimatedObject::GetFrontVector() const {
    return glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), position - center));
}

AnimatedObject::AnimatedObject(const string &path, const glm::vec3& center, float r) : StaticObject(path) {
    this->angle = 0.0f;
    this->center = center;
    this->r = r;
    this->position = glm::vec3(center.x + r, center.y, center.z);
}
