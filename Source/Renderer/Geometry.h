//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_MASHPTR_H
#define TERRENRENDERING_MASHPTR_H

#include "../Engine/libs.h"

#include <string>

using namespace gl;

enum class RenderingType{
    Triangles,
    Plane
};

class Geometry {

private:
    std::string name;
    GLuint vao;
    GLuint vbo;
    GLuint elements;
    unsigned int elementsSize;
    short techniqueIndex;
    const RenderingType renderingType;

public:

    Geometry(std::string name, GLuint vbo, GLuint elements, unsigned int elementsSize, short techniqueIndex,
             RenderingType renderingType, GLuint vao);

    GLuint getVao() const;

    GLuint getVbo() const;

    GLuint getElements() const;

    unsigned int getElementsSize() const;

    short getTechniqueIndex() const;

    const GLenum getOpenGLRenderingType() const;

    const std::string &getName() const;

};


#endif //TERRENRENDERING_MASHPTR_H
