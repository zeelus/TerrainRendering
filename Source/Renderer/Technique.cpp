//
// Created by Gilbert Gwizdala on 2019-01-31.
//

#include "Technique.h"
#include <glbinding/gl/gl.h>
#include <vector>


Technique::Technique(Shader vertex, Shader fragment) {

    shader_programme = gl::glCreateProgram();
    gl::glAttachShader(shader_programme, fragment.getHandler());
    gl::glAttachShader(shader_programme, vertex.getHandler());

    gl::glLinkProgram(shader_programme);
	gl::GLint isLinked = 0;
	gl::glGetProgramiv(shader_programme, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		GLint maxLength = 0;
		glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shader_programme, maxLength, &maxLength, &infoLog[0]);
		printf("Error: %s\n", infoLog.data());

		glDeleteProgram(shader_programme);

		return;
	}


    unsigned int uniformMatricesBlockIndex = gl::glGetUniformBlockIndex(shader_programme, "Matrices");
    unsigned int uniformPointLightIndex = gl::glGetUniformBlockIndex(shader_programme, "PointLight");

	if (uniformMatricesBlockIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(shader_programme, uniformMatricesBlockIndex, matricesBlockBinding);
	}
	else
	{
		printf("Error: the uniform block \"%s\" doesn't exist in program\n", "Matrices");
	}

	if (uniformPointLightIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(shader_programme, uniformPointLightIndex, pointLightBinding);
	}
	else
	{
		printf("Error: the uniform block \"%s\" doesn't exist in program\n", "PointLight");
	}

}

GLuint Technique::getShader_programme() const {
    return shader_programme;
}
