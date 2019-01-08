//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#ifndef TESTGLEW_SHADERS_H
#define TESTGLEW_SHADERS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <exception>


enum ShaderType{ Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER };

class ShadersLoadingException: public std::exception {
    //virtual char* what() const throw() {
    //    std::string errorString = "Shader dont find";
    //    return const_cast<char *>(errorString.c_str());
    //}
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
