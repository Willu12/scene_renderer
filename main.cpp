#include "include/glad/glad.h"


#include "include/model.hpp"
#include "include/shaders.hpp"
#include "include/bezier_plane.hpp"
#include <iostream>
#include "include/gui.hpp"
#include "include/animated_object.hpp"
#include "include/catbus.hpp"
#include "include/house.hpp"
#include "include/camera_controller.hpp"
#include <GLFW/glfw3.h>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
   // stbi_set_flip_vertically_on_load(true);

    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PUB STUDENT", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

// Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();


    Shader model_shader = Shader("../src/shaders/modelVertex.glsl",
                                 "../src/shaders/modelFragment.glsl");

    //Model ourModel(std::filesystem::path("../src/resources/models/backpack/backpack.obj"));
    auto cat = CatBus(glm::vec3(0.0f,0.0f,0.3f),0.4f);//AnimatedObject("../src/resources/models/cat/untitled.obj");
    auto house1 = House(glm::vec3(-0.3f,-0.3f,0.0f),0.0f);
    auto house2 = House(glm::vec3(-0.3f,0.3f,0.0f),0.0f);
    auto house3 = House(glm::vec3(0.3f,0.0f,0.0f),180.0f);


    StaticObject* objects[4] = {&cat,&house1, &house2,&house3};


    //create Cameras
    CameraController cameraController(window,&cat);
    Bezier_plane bezierPlane;

    SceneConfiguration sceneConfig;
    sceneConfig.tesselationLevel = 16;
    sceneConfig.day = true;
    sceneConfig.fog = false;
    sceneConfig.fogIntensity = 0.5f;
    sceneConfig.kaDay = 0.25f;
    sceneConfig.kaNight = 0.02f;
    sceneConfig.kd = 0.7f;
    sceneConfig.ks = 1.0f;
    sceneConfig.m = 20;
    sceneConfig.k = 1;

    Gui gui(&sceneConfig, &bezierPlane);


    glEnable(GL_DEPTH_TEST);
    bool guiShowed;


//     camera = catModel.pov_camera;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        gui.Show(&guiShowed);

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(StaticObject* object : objects) {
            object->Draw(model_shader,cameraController.GetCamera());
        }
        bezierPlane.Draw(cameraController.GetCamera());

        //cameraController.GetCamera()->process_key();
        cameraController.HandleInput();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}