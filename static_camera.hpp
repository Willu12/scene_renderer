#include "camera.hpp"

class StaticCamera : public Camera {
public:
    StaticCamera(GLFWwindow* window) : Camera(window) {};
    void process_key() override {};
};