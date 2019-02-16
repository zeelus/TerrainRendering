//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_MASHPTR_H
#define TERRENRENDERING_MASHPTR_H

#include <glbinding/gl/gl.h>
#include <string>

using namespace gl;

class MashPtr {

public:

    GLuint vao;
    GLuint vbo;
    GLuint elements;
    unsigned int elementsSize;
    std::string technique;

    MashPtr(GLuint vao, GLuint vbo, GLuint elements, unsigned int elementsSize, std::string technique);

};


#endif //TERRENRENDERING_MASHPTR_H
