#include "include/camera.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(GLFWwindow* window) : window(window) {
    position = glm::vec3(1.0,1.0,1.0);
    target = glm::vec3(0.0,0.0,0.0);
    direction = glm::vec3(0.0,0.0,1.0);
    zoom = 45.0f;
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position,target,direction);
}

void Camera::rotate_horizontal(float angle) {
    spherical_position spherical = get_spherical_coordinates();
    if(abs(spherical.theta + angle) > M_PI_2) return;
    spherical.theta += angle;
    update_position_from_spherical(spherical);
}

void Camera::rotate_vertical(float angle) {
    spherical_position spherical = get_spherical_coordinates();
    if(abs(spherical.phi + angle) > M_PI_2) return;
    spherical.phi += angle;
    update_position_from_spherical(spherical);
}

void Camera::update_position_from_spherical(const spherical_position &sphericalPosition) {
    position.x = sphericalPosition.r * cos(sphericalPosition.theta) * cos(sphericalPosition.phi);
    position.y = sphericalPosition.r * cos(sphericalPosition.theta) * sin(sphericalPosition.phi);
    position.z = sphericalPosition.r * sin(sphericalPosition.theta);
}

spherical_position Camera::get_spherical_coordinates() const {
    float r = sqrt((glm::dot(position,position)));
    float theta = asin(position.z / r);
    float phi = atan(position.y/ position.x);

    return {r,theta,phi};
}

void Camera::process_key() {
    const float camera_speed = 0.01f;
    const float zoom_speed = 0.2f;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotate_horizontal(camera_speed);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotate_horizontal(-camera_speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotate_vertical(-camera_speed);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotate_vertical(camera_speed);
    if(glfwGetKey(window,GLFW_KEY_Z) == GLFW_PRESS)
       // zoom += zoom_speed;
        zoom = zoom + zoom_speed > 45.0f ? 45.0f : zoom + zoom_speed;

    if(glfwGetKey(window,GLFW_KEY_X) == GLFW_PRESS)
       // zoom -= zoom_speed;
        zoom = zoom - zoom_speed < 1.0f ? 1.0f : zoom - zoom_speed;
}

glm::mat4 Camera::GetProjectionMatrix() const{
    int width, height;
    glfwGetFramebufferSize(window,&width,&height);
    return glm::perspective(glm::radians(zoom), (float)width/(float)height, 0.1f, 100.0f);
}