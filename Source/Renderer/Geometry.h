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
    GLuint vao;
    GLuint vbo;
    GLuint elements;
    unsigned int elementsSize;
    short techniqueIndex;
    const RenderingType renderingType;

public:

    Geometry(GLuint vao, GLuint vbo, GLuint elements, unsigned int elementsSize, short techniqueIndex, RenderingType renderingType);

    GLuint getVao() const;

    GLuint getVbo() const;

    GLuint getElements() const;

    unsigned int getElementsSize() const;

    short getTechniqueIndex() const;

    const GLenum getOpenGLRenderingType() const;


};


#endif //TERRENRENDERING_MASHPTR_H
