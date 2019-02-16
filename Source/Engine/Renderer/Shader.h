//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#ifndef TESTGLEW_SHADERS_H
#define TESTGLEW_SHADERS_H

#include <glbinding/gl/gl.h>
#define GLFW_INCLUDE_NONE
#include <string>
#include <exception>

using namespace gl;


enum ShaderType { Vertex,
    Fragment };

class ShadersLoadingException: public std::runtime_error {

public:
    ShadersLoadingException(std::string& location): std::runtime_error("Shader file load " + location) {};

};

class Shader {

    ShaderType type;

    std::string shaderCode;

    GLuint handler = 0;
public:
    GLuint getHandler() const;

public:

    Shader(ShaderType type, std::string path);
    ShaderType getType() const;

private:

    void loadShaders(std::string& path);
    void compilateShader();

};


#endif //TESTGLEW_SHADERS_H
