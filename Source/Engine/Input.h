//
// Created by Gilbert Gwizdala on 14.03.2019.
//

#ifndef TERRENRENDERING_INPUT_H
#define TERRENRENDERING_INPUT_H
#include "libs.h"

#include <vector>
#include <set>
#include <functional>

class Input {

    static Input* instance;

	std::set<int> pressedButton;

public:
    static Input* getInstance();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods);

	const bool isPreeed(const int& key) const;


};


#endif //TERRENRENDERING_INPUT_H
