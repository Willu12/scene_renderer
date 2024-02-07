#pragma once
#include "animated_object.hpp"

#include "camera.hpp"
#include <GLFW/glfw3.h>


class ThirdPersonCamera : public Camera {
public:
    ThirdPersonCamera(GLFWwindow* window, AnimatedObject* animatedObject, float r, float angle) : Camera(window),
    animatedObject(animatedObject), r(r), angle(angle) {}
    glm::mat4 GetViewMatrix() const override;


private:
    AnimatedObject* animatedObject;
    float r, angle;
    glm::vec3 GetCameraPosition() const;
};