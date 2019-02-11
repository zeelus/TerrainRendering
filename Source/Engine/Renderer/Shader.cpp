//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include "Shader.h"
#include <GL/glew.h>
#include <fstream>

Shader::Shader(ShaderType type, std::string path) {
    this->type = type;
    this->loadShaders(path);
    this->compilateShader();
}

ShaderType Shader::getType() const {
    return type;
}

void Shader::loadShaders(std::string &path) {

    std::ifstream file;
    std::string line;

    file.open(path);

    if(file.is_open()) {
        while ( getline (file, line) )
        {
            shaderCode += line;
            shaderCode += "\n";
        }
    } else {
        throw ShadersLoadingException(path);
    }

    file.close();

}

void Shader::compilateShader() {

    handler = glCreateShader(type);
    char* shaderSource = const_cast<char*>(shaderCode.c_str());
    glShaderSource(handler, 1, &shaderSource, NULL);
    glCompileShader(handler);

    GLint isCompiled = 0;
    glGetShaderiv(handler, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        std::string name("Compied error");
        throw ShadersLoadingException(name);
    }

}

GLuint Shader::getHandler() const {
    return handler;
}
