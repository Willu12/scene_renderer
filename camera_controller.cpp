#include "include/camera_controller.hpp"

const Camera& CameraController::GetCamera() {
    return *activeCamera;
}

void CameraController::HandleInput() {
    if (glfwGetKey(window,GLFW_KEY_1) == GLFW_PRESS) {
        activeCamera = (Camera*) staticCamera;
    }
    if (glfwGetKey(window,GLFW_KEY_2) == GLFW_PRESS) {
        activeCamera = (Camera*) followObjectCamera;
    }
    if (glfwGetKey(window,GLFW_KEY_3) == GLFW_PRESS) {
        activeCamera = (Camera*) thirdPersonCamera;
    }
    if (glfwGetKey(window,GLFW_KEY_4) == GLFW_PRESS) {
        activeCamera = (Camera*) freeCamera;
    }
    activeCamera->process_key();
}