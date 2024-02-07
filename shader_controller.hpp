#pragma once

#include "scene_configuration.hpp"
#include "shaders.hpp"

enum ShadingModel {
    FlatShadingModel,
    GourandShadingModel,
    PhongShadingModel
};

class ShaderController {
public:
    ShaderController(SceneConfiguration* sceneConfiguration) {
        this->sceneConfig = sceneConfig;
        phongSurfaceShader = new Shader("./shaders/vert/surface.glsl",
                                        "./shaders/tessControl/default.glsl",
                                        "./shaders/tessEval/default.glsl",
                                        "./shaders/frag/phong.glsl");

        gourandSurfaceShader = new Shader("./shaders/vert/surface.glsl",
                                          "./shaders/tessControl/default.glsl",
                                          "./shaders/tessEval/gourand.glsl",
                                          "./shaders/frag/gourand.glsl");

        flatSurfaceShader = new Shader("./shaders/vert/surface.glsl",
                                       "./shaders/tessControl/default.glsl",
                                       "./shaders/tessEval/flat.glsl",
                                       "./shaders/frag/flat.glsl");

        phongModelShader = new Shader("./shaders/vert/model_phong.glsl",
                                      "./shaders/frag/phong.glsl");

        gourandModelShader = new Shader("./shaders/vert/model_gourand.glsl",
                                        "./shaders/frag/gourand.glsl");

        flatModelShader = new Shader("./shaders/vert/model_flat.glsl",
                                     "./shaders/frag/flat.glsl");

        activeModel = PhongShadingModel;
    }

    Shader* GetModelShader();
    Shader* GetSurfaceShader();
    ShadingModel GetShadingModel();
    void SetShadingModel(ShadingModel model);
private:
    void LoadSceneConfiguration(Shader* shader);
    SceneConfiguration* sceneConfig;
    Shader* flatModelShader;
    Shader* gourandModelShader;
    Shader* phongModelShader;
    Shader* flatSurfaceShader;
    Shader* gourandSurfaceShader;
    Shader* phongSurfaceShader;
    ShadingModel activeModel;
};