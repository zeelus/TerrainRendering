//
// Created by Gilbert Gwizdala on 2019-08-05.
//

#ifndef TERRENRENDERING_UNIFORM_H
#define TERRENRENDERING_UNIFORM_H

#include <vector>
#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>
#include <string>

class Uniform {

    const std::string name;

    unsigned int bindingPoint = -1;

    unsigned int uniformHandler = -1;

public:

    Uniform();

    explicit Uniform(std::string name, unsigned int bindingPoint);

private:

    std::vector<glm::vec4> data;

};


#endif //TERRENRENDERING_UNIFORM_H
