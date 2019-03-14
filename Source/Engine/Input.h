//
// Created by Gilbert Gwizdala on 14.03.2019.
//

#ifndef TERRENRENDERING_INPUT_H
#define TERRENRENDERING_INPUT_H
#include "libs.h"

#include <vector>
#include <functional>

class Input {

    static Input* instance;

    std::vector<std::function<void(int, int, int, int)>> functions;

public:
    static Input* getInstance();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods);

    void addFunction(const std::function<void(int, int, int, int)> function);

};


#endif //TERRENRENDERING_INPUT_H
