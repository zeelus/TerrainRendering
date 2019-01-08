//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#include "Renderer.h"

#include <string>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

Renderer::Renderer(float width, float height, std::string &name): width(width), height(height), name(name){

}

int Renderer::setupWindow() {


    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, name.c_str(), NULL, NULL);

    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwInit();

    showOpenGLInformations();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return 0;
}

void Renderer::showOpenGLInformations() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}

GLFWwindow *Renderer::getWindow() const {
    return window;
}

void Renderer::drowing() {
    float points[] = {
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    static const GLfloat color_buffer[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    Shader vertex(Vertex, "Resources/Shaders/VertexShader.vert");
    Shader fragment(Fragment, "Resources/Shaders/FragmentShader.frag");

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fragment.getHandler());
    glAttachShader(shader_programme, vertex.getHandler());
    glLinkProgram(shader_programme);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, &Renderer::key_callback_static);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_programme);

        camera.update(shader_programme);

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }


    glfwTerminate();
}

void Renderer::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto renderer = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->key_callback(window, key, scancode, action, mods);
}

void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto pos = camera.getView();
    mat4 newPos = pos;
    switch (key) {
        case GLFW_KEY_W:
            newPos = glm::translate(pos, vec3(-0.2f, 0.0f, 0.0f));
            break;
        case GLFW_KEY_S:
            newPos = glm::translate(pos, vec3(0.2f, 0.0f, 0.0));
            break;
        case GLFW_KEY_D:
            newPos = glm::translate(pos, vec3(0.0f, 0.0f, -0.2f));
            break;
        case GLFW_KEY_A:
            newPos = glm::translate(pos, vec3(0.0f, 0.0f, 0.2f));
            break;
    }

    camera.setView(newPos);
}

