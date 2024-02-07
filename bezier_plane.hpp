#pragma once

#include "camera.hpp"

#include <iostream>

class Bezier_plane {
public:
    unsigned int vao,vbo, ebo, program;
    float vertices[48];
    Bezier_plane();
    ~Bezier_plane();
    void Draw(const Camera& camera, Shader& shader);

private:
    unsigned int tesselation_level;
    static const std::string vs_path;
    static const std::string fs_path;
    static const std::string tsc_path;
    static const std::string ts_path;

    void set_uniforms(const Camera& camera);
    void set_matrices(const Camera& camera) const;
    void init_bezier_plane();
};
