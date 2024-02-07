#include "include/follow_object_camera.hpp"

glm::mat4 FollowObjectCamera::GetViewMatrix() const {
    return glm::lookAt(position, animatedObject->GetPosition(), glm::vec3(0.0f, 0.0f, 1.0f));
}