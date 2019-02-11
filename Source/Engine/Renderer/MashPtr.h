//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_MASHPTR_H
#define TERRENRENDERING_MASHPTR_H

#include <GL/glew.h>
#include <string>

class MashPtr {

public:

    GLuint vbo;
    GLuint elements;
    int elementsSize;
    std::string technique;

    MashPtr(GLuint vbo, GLuint elements, unsigned int elementsSize, std::string technique);

};


#endif //TERRENRENDERING_MASHPTR_H
