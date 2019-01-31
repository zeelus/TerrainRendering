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


    Shader vertex(Vertex, "Resources/Shaders/VertexShader.vert");
    Shader fragment(Fragment, "Resources/Shaders/FragmentShader.frag");
    technique = new Technique(vertex, fragment);

    float points[] = {
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            1.0,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f
    };

    GLushort cube_elements[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint index_buffer_handle = 0;
    glGenBuffers(1, &index_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(vao);

}

void Renderer::drowing() {

    auto shader_programme = technique->getShader_programme();

    glUseProgram(shader_programme);

    this->updateCamera(shader_programme);

    //glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

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
