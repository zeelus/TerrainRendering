//
// Created by Gilbert Gwizdala on 2019-01-31.
//
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <boost/algorithm/string.hpp>

#include "ResorceManager.h"

using namespace std;

void ResorceManager::loadOBJModel(const std::string& path) {

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<GLshort> elements;

    ifstream file(path);

    if(!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            istringstream lineString(line.substr(2));
            glm::vec3 v;

            lineString >> v.x;
            lineString >> v.y;
            lineString >> v.z;

            vertices.push_back(v);
        } else if (line.substr(0, 2) == "f ") {
            auto newLine = line.substr(2);
            vector<string> strs;
            std::vector<std::string> tokens;
            boost::algorithm::split(tokens, newLine, boost::is_any_of(" "));

            for (auto &element: tokens) {
                if (element.empty()) continue;
                boost::algorithm::replace_all(element, "/", " ");
                istringstream elementLine(element);
                GLshort x;
                elementLine >> x;
                x--;
                elements.push_back(x);
            }


        }
    }

        normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
        for (int i = 0; i < elements.size(); i+=3)
        {
            GLushort ia = elements[i];
            GLushort ib = elements[i+1];
            GLushort ic = elements[i+2];
            glm::vec3 normal = glm::normalize(glm::cross(
                    glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
                    glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
            normals[ia] = normals[ib] = normals[ic] = normal;
        }


    int x = 3;
    file.close();

}
