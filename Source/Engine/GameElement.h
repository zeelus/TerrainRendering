//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#ifndef TERRENRENDERING_GAMEELEMENT_H
#define TERRENRENDERING_GAMEELEMENT_H

#include <string>
#include <entt/entity/registry.hpp>
#include <entt/entt.hpp>
#include <type_traits>
#include "Component/Component.h"


class GameElement {
    std::string name;
    entt::registry<>* registryEntt;
    unsigned int entity;
public:
    GameElement(std::string name, entt::registry<>* registryEntt);

    template<class T> T& createComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        auto componentType = registryEntt->assign<T>(entity);
        auto component = static_cast<Component>(componentType);
        return componentType;
    }
};


#endif //TERRENRENDERING_GAMEELEMENT_H
