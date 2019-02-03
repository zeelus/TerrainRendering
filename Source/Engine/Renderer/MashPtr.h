//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_MASHPTR_H
#define TERRENRENDERING_MASHPTR_H

#include <GL/glew.h>

class MashPtr {

public:
    GLuint vbo;
    GLuint elements;
    int elementsSize;

    MashPtr(GLuint vbo, GLuint elements, int elementsSize);

};


#endif //TERRENRENDERING_MASHPTR_H
