#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "scene_configuration.hpp"
#include "bezier_plane.hpp"

class Gui {
public:
    Gui(SceneConfiguration* sceneConfig, Bezier_plane* bezierPlane);
    void Show(bool* p_open);
    void LoadTextureButton(const char* id, const char* text, GLuint* texture);
private:
    SceneConfiguration* sceneConfig;
    Bezier_plane* bezierPlane;
};