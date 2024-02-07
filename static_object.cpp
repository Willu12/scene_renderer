#include "include/static_object.hpp"

StaticObject::StaticObject(Model &model) {
    this->model = &model;
}

StaticObject::StaticObject(const std::string &path) {
  //  Model new_model((std::filesystem::path(path)));
    this->model = new Model(std::filesystem::path(path));
}

void StaticObject::Draw(Shader& shader,const Camera& camera) {
    this->model->setup_shader(shader,camera);
    this->model->Draw(shader);
}