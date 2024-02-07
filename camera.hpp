#pragma once
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class spherical_position {
public:
    float r, theta, phi;
    spherical_position(float r_m, float theta_m, float phi_m) {
        r = r_m;
        theta = theta_m;
        phi = phi_m;
    }
};

class Camera {
public:
    glm::vec3 position{}, target{}, direction{};
    float zoom;
    Camera(GLFWwindow* window);
    void rotate_vertical(float angle);
    void rotate_horizontal(float angle);
    virtual void process_key();
    virtual glm::mat4 GetViewMatrix() const;
    virtual glm::mat4 GetProjectionMatrix() const;

private:
    GLFWwindow* window;
    spherical_position get_spherical_coordinates() const;
    void update_position_from_spherical(const spherical_position& sphericalPosition);
};