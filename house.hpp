#include "static_object.hpp"

class House : public StaticObject {
public:
    House(const glm::vec3& position, float angle);
private:
    const float scale = 0.01f;
};