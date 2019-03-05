//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#include "Geometry.h"

Geometry::Geometry(GLuint vao, GLuint vbo, GLuint elements, unsigned int elementsSize, short techniqueIndex): vao(vao),
                                                                                                                vbo(vbo),
                                                                                                                elements(elements),
                                                                                                                elementsSize(elementsSize),
                                                                                                                techniqueIndex(techniqueIndex)
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
