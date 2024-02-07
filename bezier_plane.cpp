#include "include/shaders.hpp"
#include "include/bezier_plane.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int link_program(const std::string& vs_path, const std::string& fs_path,const std::string& tsc_path, const std::string& ts_path);
void init_bezier_plane(Bezier_plane& bezierPlane);

const std::string Bezier_plane::vs_path = "../src/shaders/vertexShader.glsl";
const std::string Bezier_plane::fs_path = "../src/shaders/fragmentShader.glsl";
const std::string Bezier_plane::tsc_path ="../src/shaders/tessellationControlShader.glsl";
const std::string Bezier_plane::ts_path = "../src/shaders/tessellationEvaluationShader.glsl";

Bezier_plane::Bezier_plane() : vertices() {
    vao = vbo = ebo = program = 0;
    tesselation_level = 32;

    float initialVertices[] = {
            -0.75, -0.75, 0.0, -0.25, -0.75, 0.0,
            0.25, -0.75, 0.0,  0.75, -0.75, 0.0,
            -0.75, -0.25, 0.0, -0.25, -0.25, 0.0,
            0.25, -0.25, 0.0,  0.75, -0.25, 0.0,
            -0.75,  0.25, 0.0, -0.25,  0.25, 0.0,
            0.25,  0.25, 0.0,  0.75,  0.25, 0.0,
            -0.75,  0.75, 0.0, -0.25,  0.75, 0.0,
            0.25,  0.75, 0.0,  0.75,  0.75, 0.0
    };

    // Copy the values to the class member
    std::copy(std::begin(initialVertices), std::end(initialVertices), std::begin(vertices));


   Bezier_plane::program =  link_program(Bezier_plane::vs_path,Bezier_plane::fs_path,
                                        Bezier_plane::tsc_path,Bezier_plane::ts_path);

   init_bezier_plane();

   glGenVertexArrays(1,&vao);
   glGenBuffers(1,&vbo);
   glGenBuffers(1,&ebo);
}

Bezier_plane::~Bezier_plane() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Bezier_plane::Draw(const Camera& camera) {
    init_bezier_plane();
    glBindVertexArray(vao);
    glUseProgram(program);
    set_uniforms(camera);
    glDrawArrays(GL_PATCHES,0,16);
}

void Bezier_plane::set_uniforms(const Camera& camera) {
    int light_pos_location = glGetUniformLocation(program, "lightPos");
    int camera_pos_location = glGetUniformLocation(program, "cameraPos");
    int object_color_location = glGetUniformLocation(program, "objectColor");
    int light_color_location = glGetUniformLocation(program, "lightColor");
    int kd_location = glGetUniformLocation(program, "kd");
    int ks_location = glGetUniformLocation(program, "ks");
    int m_location = glGetUniformLocation(program, "m");
    int tessellation_level_location = glGetUniformLocation(program, "TessLevel");

    set_matrices(camera);

    glUniform1ui(tessellation_level_location, tesselation_level);
    glUniform3f(light_pos_location, 1.0, 1.0, 1.0);
    glUniform3f(camera_pos_location, camera.position.x, camera.position.y, camera.position.z);
    glUniform3f(light_color_location, 155, 155, 155);
    glUniform3f(object_color_location, 100, 100, 100);
    glUniform1f(kd_location, 0.5);
    glUniform1f(ks_location, 0.5);
    glUniform1ui(m_location, 20);

}

void Bezier_plane::set_matrices(const Camera& camera) const {
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = projection * view * model;
    glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view)));

    GLint mvp_location = glGetUniformLocation(program, "MVP");
    GLint view_location = glGetUniformLocation(program, "ModelViewMatrix");
    GLint normal_location = glGetUniformLocation(program, "NormalMatrix");

// Set the uniform values
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix3fv(normal_location, 1, GL_FALSE, glm::value_ptr(normal));

}

unsigned int link_program(const std::string& vs_path, const std::string& fs_path,const std::string& tsc_path, const std::string& ts_path) {

    //create shaders
    Shader vs_shader = Shader(vs_path,GL_VERTEX_SHADER);
    Shader fs_shader = Shader(fs_path,GL_FRAGMENT_SHADER);
    Shader tsc_shader = Shader(tsc_path, GL_TESS_CONTROL_SHADER);
    Shader ts_shader = Shader(ts_path,GL_TESS_EVALUATION_SHADER);
    unsigned int program = glCreateProgram();

    glAttachShader(program,vs_shader.ID);
    glAttachShader(program,fs_shader.ID);
    glAttachShader(program,tsc_shader.ID);
    glAttachShader(program,ts_shader.ID);

    glLinkProgram(program);
    Shader::checkCompileErrors(program, "PROGRAM");

    glDetachShader(program,vs_shader.ID);
    glDetachShader(program,fs_shader.ID);
    glDetachShader(program,tsc_shader.ID);
    glDetachShader(program,ts_shader.ID);

    glDeleteShader(vs_shader.ID);
    glDeleteShader(fs_shader.ID);
    glDeleteShader(tsc_shader.ID);
    glDeleteShader(ts_shader.ID);

    return program;
}


void Bezier_plane::init_bezier_plane(){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), nullptr);

    glEnableVertexAttribArray(0);
    glPatchParameteri(GL_PATCH_VERTICES,16);
}