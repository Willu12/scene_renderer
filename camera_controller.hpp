#pragma once

#include "animated_object.hpp"
#include "camera.hpp"
#include "static_camera.hpp"
#include "follow_object_camera.hpp"
#include "third_person_camera.hpp"

class CameraController {
public:
    CameraController(GLFWwindow* window, AnimatedObject* animatedObject) {
        this->window = window;
        this->staticCamera = new StaticCamera(window);
        this->followObjectCamera = new FollowObjectCamera(window,animatedObject,glm::vec3(0.5f,0.5f,0.5f));
        this->freeCamera = new Camera(window);
        this->thirdPersonCamera = new ThirdPersonCamera(window,animatedObject,0.5f,20.0f);
        this->activeCamera = staticCamera;
    }
    void HandleInput();
    const Camera& GetCamera();

    private:
    GLFWwindow* window;
    Camera* activeCamera;
    StaticCamera* staticCamera;
    ThirdPersonCamera* thirdPersonCamera;
    Camera* freeCamera;
    FollowObjectCamera* followObjectCamera;
};