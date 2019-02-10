//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_STATICMODEL_H
#define TERRENRENDERING_STATICMODEL_H

#include <glm/glm.hpp>
#include "MashPtr.h"

class StaticModel {

    glm::mat4 transform = glm::mat4(1.0f);
    MashPtr* mashPtr;

public:
    MashPtr *getMashPtr() const;

    StaticModel(MashPtr* mashPtr);

    const glm::mat4 &getTransform() const;
    void setTransform(const glm::mat4 &transform);

    void setPosition(const glm::vec3 &position);
    const glm::vec3 getPosition() const;

    void rotate(GLfloat angle, glm::vec3 vector);

};


#endif //TERRENRENDERING_STATICMODEL_H
