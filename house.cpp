#include "include/house.hpp"
const char* HousePath =  "../src/resources/models/house/scene.gltf";


House::House(const glm::vec3& position, float angle) : StaticObject(HousePath), scale(0.01f) {
    glm::mat4 mm(1.0f);
    mm = glm::translate(mm, position);
    mm = glm::rotate(mm,1.5f,glm::vec3(1.0,0.0,0.0));
    mm = glm::rotate(mm, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    mm = glm::scale(mm, glm::vec3(scale, scale, scale));
    this->model->model_matrix = mm;
}
