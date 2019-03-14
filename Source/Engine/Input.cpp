//
// Created by Gilbert Gwizdala on 14.03.2019.
//

#include "Input.h"

Input* Input::instance = nullptr;

Input *Input::getInstance() {
    if(!instance) {
        instance = new Input();
    }

    return instance;
}

void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    for(auto& func: functions) {
        func(key, scancode, action, mods);
    }
}

void Input::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto inputSystem = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));
    inputSystem->key_callback(window, key, scancode, action, mods);
}

void Input::addFunction(const std::function<void(int, int, int, int)> function) {
    this->functions.push_back(function);
}
