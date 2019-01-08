//
// Created by Gilbert Gwizdala on 2018-12-19.
//

#include <string>
#include "Renderer/Renderer.h"

int main() {

    std::string windowName = "Terrain renderer";
    Renderer renderer(800, 600, windowName);

    if (renderer.setupWindow() == -1) {
        fprintf(stderr, "Setup window error! \n");
        return 1;
    }

    renderer.drowing();

    return 0;
}

