//
// Created by Gilbert Gwizdala on 2019-08-05.
//

#include <array>
#include "UniformManager.h"
#include "Uniform.h"

UniformManager* UniformManager::instance = nullptr;

UniformManager *UniformManager::getInstance() {
    if(UniformManager::instance == nullptr) {
        UniformManager::instance = new UniformManager();
    }

    return  UniformManager::instance;
}

void UniformManager::initUniforms() {

    std::array<UniformType, 3u> uboArray = {UniformType::Metrics, UniformType::PointLight, UniformType::Terrain};

    for(auto& type: uboArray) {
        unsigned int bindingPoint = static_cast<typename std::underlying_type<UniformType>::type>(type);
        std::string name;
        switch(type) {
            case UniformType::Metrics:
                name = "Matrices";
                break;
        }


        Uniform uniform(name, bindingPoint);
        map.insert({type, uniform});
    }

}

Uniform &UniformManager::getUniform(UniformType type){
    return map[type];
}
