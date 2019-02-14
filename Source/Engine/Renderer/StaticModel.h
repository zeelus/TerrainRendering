//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#ifndef TERRENRENDERING_STATICMODEL_H
#define TERRENRENDERING_STATICMODEL_H

#include <glm/glm.hpp>
#include "MashPtr.h"

class StaticModel {

    glm::mat4 transform = glm::mat4(1.0f);
    int indexMashPtr;

public:
    int getIndexMashPtr() const;

    explicit StaticModel(unsigned int indexMashPtr);

    const glm::mat4 &getTransform() const;
    void setTransform(const glm::mat4 &transform);

    void setPosition(const glm::vec3 &position);
    const glm::vec3 getPosition() const;

    void rotate(GLfloat angle, glm::vec3 vector);
    void scale(const glm::vec3 &scale);

};


#endif //TERRENRENDERING_STATICMODEL_H
