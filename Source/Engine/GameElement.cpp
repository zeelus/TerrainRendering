//
// Created by Gilbert Gwizdala on 2019-01-26.
//

#include "GameElement.h"

GameElement::GameElement(std::string name, entt::registry<>* registryEntt): name(name), registryEntt(registryEntt) {
    entity = registryEntt->create();
}
