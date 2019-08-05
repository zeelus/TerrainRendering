//
// Created by Gilbert Gwizdala on 2019-08-05.
//

#ifndef TERRENRENDERING_UNIFORMMANAGER_H
#define TERRENRENDERING_UNIFORMMANAGER_H

#include "Uniform.h"
#include <map>

enum class UniformType: int {
    Metrics = 0, PointLight = 1, Terrain = 2
};

class UniformManager {

    static UniformManager* instance;

    std::map<UniformType, Uniform> map;

public:

    static UniformManager* getInstance();

    void initUniforms();

    Uniform& getUniform(UniformType type);

};


#endif //TERRENRENDERING_UNIFORMMANAGER_H
