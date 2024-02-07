#include "include/catbus.hpp"
const char* CatPath =  "../src/resources/models/cat/untitled.obj";

CatBus::CatBus(const glm::vec3& center, float r) : AnimatedObject(CatPath,center,r){};