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
		glUniformBlockBinding(shader_programme, uniformMatricesBlockIndex, MatricesBlockBinding);
	}
	else
	{
		printf("Error: the uniform block \"%s\" doesn't exist in program\n", "Matrices");
	}

	if (uniformPointLightIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(shader_programme, uniformPointLightIndex, PointLightBinding);
	}
	else
	{
		printf("Error: the uniform block \"%s\" doesn't exist in program\n", "PointLight");
	}

}

Technique::Technique(Shader vertex, Shader fragment, Shader geometry) {

	shader_programme = gl::glCreateProgram();
	gl::glAttachShader(shader_programme, fragment.getHandler());
	gl::glAttachShader(shader_programme, geometry.getHandler());
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
	unsigned int uniformTerrainIndex = gl::glGetUniformBlockIndex(shader_programme, "Terrain");

	if (uniformMatricesBlockIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(shader_programme, uniformMatricesBlockIndex, MatricesBlockBinding);
	}
	else
	{
		printf("Error: the uniform block \"%s\" doesn't exist in program\n", "Matrices");
	}

	if (uniformPointLightIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(shader_programme, uniformPointLightIndex, PointLightBinding);
	}
	else
	{
		printf("Error: the uniform block \"%s\" doesn't exist in program\n", "PointLight");
	}

	if (uniformTerrainIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(shader_programme, uniformTerrainIndex, TerrainBinding);
	}
	else
	{
		printf("The uniform block \"%s\" doesn't exist in program\n", "TerrainBinding");
	}
}

Technique::Technique(Shader vertex, Shader fragment, Shader geometry, Shader tControl, Shader tEval) {
    shader_programme = gl::glCreateProgram();
    gl::glAttachShader(shader_programme, fragment.getHandler());
    gl::glAttachShader(shader_programme, geometry.getHandler());
    gl::glAttachShader(shader_programme, vertex.getHandler());
    gl::glAttachShader(shader_programme, tControl.getHandler());
    gl::glAttachShader(shader_programme, tEval.getHandler());

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
    unsigned int uniformTerrainIndex = gl::glGetUniformBlockIndex(shader_programme, "Terrain");

    if (uniformMatricesBlockIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(shader_programme, uniformMatricesBlockIndex, MatricesBlockBinding);
    }
    else
    {
        printf("Error: the uniform block \"%s\" doesn't exist in program\n", "Matrices");
    }

    if (uniformPointLightIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(shader_programme, uniformPointLightIndex, PointLightBinding);
    }
    else
    {
        printf("Error: the uniform block \"%s\" doesn't exist in program\n", "PointLight");
    }

    if (uniformTerrainIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(shader_programme, uniformTerrainIndex, TerrainBinding);
    }
    else
    {
        printf("The uniform block \"%s\" doesn't exist in program\n", "TerrainBinding");
    }
}

GLuint Technique::getShader_programme() const {
    return shader_programme;
}
