//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include "Shader.h"
#include <glbinding/gl/gl.h>
#include <fstream>

using namespace gl;

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
    switch(type) {
        case VertexShader:
            handler = glCreateShader(gl::GL_VERTEX_SHADER);
            break;
        case FragmentShader:
            handler = glCreateShader(gl::GL_FRAGMENT_SHADER);
            break;
        case GeometryShader:
            handler = glCreateShader(gl::GL_GEOMETRY_SHADER);
    }
//    handler = glCreateShader(type);
    char* shaderSource = const_cast<char*>(shaderCode.c_str());
    gl::glShaderSource(handler, 1, &shaderSource, NULL);
    gl::glCompileShader(handler);

    GLint isCompiled = 0;
    glGetShaderiv(handler, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled)
    {
        std::string name("Compied error");

		GLint maxLength = 0;
		glGetShaderiv(handler, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(handler, maxLength, &maxLength, &infoLog[0]);

		printf("Error: %s\n", infoLog.data());

		glDeleteShader(handler);

        throw ShadersLoadingException(name);
    }

}

GLuint Shader::getHandler() const {
    return handler;
}
