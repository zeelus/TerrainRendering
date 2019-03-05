//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_MASHPTR_H
#define TERRENRENDERING_MASHPTR_H

#include <glbinding/gl/gl.h>
#include <string>

using namespace gl;

class Geometry {

private:
    GLuint vao;
    GLuint vbo;
    GLuint elements;
    unsigned int elementsSize;
    short techniqueIndex;

public:

    Geometry(GLuint vao, GLuint vbo, GLuint elements, unsigned int elementsSize, short techniqueIndex);

    GLuint getVao() const;

    GLuint getVbo() const;

    GLuint getElements() const;

    unsigned int getElementsSize() const;

    short getTechniqueIndex() const;

};


#endif //TERRENRENDERING_MASHPTR_H
