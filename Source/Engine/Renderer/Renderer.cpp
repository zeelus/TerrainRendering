//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#include "Renderer.h"

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include <entt/entt.hpp>

Renderer::Renderer() {

}

void Renderer::init() {

    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &ubo_matrix_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrix_handle);
    std::array<glm::mat4x4, 3u> matrices = { camera.model, camera.view, camera.project};
    glBufferData(GL_UNIFORM_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    Shader vertex(Vertex, "Resources/Shaders/VertexShader.vert");
    Shader fragment(Fragment, "Resources/Shaders/FragmentShader.frag");
    technique = new Technique(vertex, fragment);

}

void Renderer::draw() {
    drawStaticModels();
}

void Renderer::drawStaticModels() {
    auto shader_programme = technique->getShader_programme();

    glUseProgram(shader_programme);

    updateCamera(shader_programme);

    for(auto& model: staticModels) {
        glBindVertexArray(vao);
        glEnableVertexAttribArray(vertex_position_loction);
        glBindBuffer(GL_ARRAY_BUFFER, model.getMashPtr()->vbo);
        glVertexAttribPointer(vertex_position_loction, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

        glEnableVertexAttribArray(vertex_normal_loction);
        glVertexAttribPointer(vertex_normal_loction, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3*sizeof(GLfloat)));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.getMashPtr()->elements);
        glBindVertexArray(0u);

        glBindBuffer(GL_ARRAY_BUFFER, 0u);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, model.getMashPtr()->elementsSize * sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(0u);
    }
}

void Renderer::updateCamera(GLuint shader_programme) {
    this->camera.update(shader_programme);
}

Renderer::~Renderer() {
    delete technique;
}

//void Renderer::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    auto rendererSystem = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
//    rendererSystem->key_callback(window, key, scancode, action, mods);
//}
//
//void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    auto pos = camera.getView();
//    mat4 newPos = pos;
//    switch (key) {
//        case GLFW_KEY_W:
//            newPos = glm::translate(pos, vec3(-0.2f, 0.0f, 0.0f));
//            break;
//        case GLFW_KEY_S:
//            newPos = glm::translate(pos, vec3(0.2f, 0.0f, 0.0));
//            break;
//        case GLFW_KEY_D:
//            newPos = glm::translate(pos, vec3(0.0f, 0.0f, -0.2f));
//            break;
//        case GLFW_KEY_A:
//            newPos = glm::translate(pos, vec3(0.0f, 0.0f, 0.2f));
//            break;
//    }
//
//    camera.setView(newPos);
//}

