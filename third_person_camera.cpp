#include "include/third_person_camera.hpp"

glm::mat4 ThirdPersonCamera::GetViewMatrix() const {
    return glm::lookAt(GetCameraPosition(), animatedObject->GetPosition(), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 ThirdPersonCamera::GetCameraPosition() const {
    glm::vec3 position = animatedObject->GetPosition();
    glm::vec3 front = animatedObject->GetFrontVector();
    glm::mat4 rotationMatrix(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), -position);
    return position - glm::vec3(rotationMatrix * glm::vec4(front * r, 1.0f));
}
