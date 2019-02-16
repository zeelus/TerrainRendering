//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#include "Technique.h"
#include <glbinding/gl/gl.h>


Technique::Technique(Shader vertex, Shader fragment) {

    shader_programme = gl::glCreateProgram();
    gl::glAttachShader(shader_programme, fragment.getHandler());
    gl::glAttachShader(shader_programme, vertex.getHandler());
    gl::glLinkProgram(shader_programme);

    unsigned int uniformMatricesBlockIndex = gl::glGetUniformBlockIndex(shader_programme, "Matrices");
    unsigned int uniformPointLightIndex = gl::glGetUniformBlockIndex(shader_programme, "PointLight");

    gl::glUniformBlockBinding(shader_programme, uniformPointLightIndex, pointLightBinding);
    gl::glUniformBlockBinding(shader_programme, uniformMatricesBlockIndex, matricesBlockBinding);

}

GLuint Technique::getShader_programme() const {
    return shader_programme;
}
