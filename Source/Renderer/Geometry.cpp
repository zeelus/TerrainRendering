//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#include "Geometry.h"

Geometry::Geometry(
        GLuint vao,
        GLuint vbo,
        GLuint elements,
        unsigned int elementsSize,
        short techniqueIndex,
        RenderingType renderingType):
            vao(vao),
            vbo(vbo),
            elements(elements),
            elementsSize(elementsSize),
            techniqueIndex(techniqueIndex),
            renderingType(renderingType)
            {}

GLuint Geometry::getVao() const {
    return vao;
}

GLuint Geometry::getVbo() const {
    return vbo;
}

GLuint Geometry::getElements() const {
    return elements;
}

unsigned int Geometry::getElementsSize() const {
    return elementsSize;
}

short Geometry::getTechniqueIndex() const {
    return techniqueIndex;
}

const GLenum Geometry::getOpenGLRenderingType() const {
    switch(renderingType) {
        case RenderingType::Triangles:
            return gl::GL_TRIANGLES;
        case RenderingType::Plane:
            return GL_PATCHES;
    };
}


