#include "animated_object.hpp"
#include "camera.hpp"

class FollowObjectCamera : public Camera {
public:
    FollowObjectCamera(GLFWwindow* window,AnimatedObject* animatedObject, const glm::vec3& position) : Camera(window) {
        this->animatedObject = animatedObject;
        this->position = position;
    }
    void process_key() override {};
    glm::mat4 GetViewMatrix() const override;
private:
    AnimatedObject* animatedObject;
    glm::vec3 position;
};