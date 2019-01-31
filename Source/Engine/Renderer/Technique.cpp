//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#include "Technique.h"

Technique::Technique(Shader vertex, Shader fragment) {

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fragment.getHandler());
    glAttachShader(shader_programme, vertex.getHandler());
    glLinkProgram(shader_programme);

}

GLuint Technique::getShader_programme() const {
    return shader_programme;
}
