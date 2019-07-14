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

	if (action == GLFW_PRESS) {
		this->pressedButton.insert(key);
	}
	if (action == GLFW_RELEASE){
		this->pressedButton.erase(key);
	}

}

void Input::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto inputSystem = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));
    inputSystem->key_callback(window, key, scancode, action, mods);
}

const bool Input::isPreeed(const int& key) const
{

	if (pressedButton.find(key) == pressedButton.end()) {
		return false;
	} else {
		return true;
	}

}

