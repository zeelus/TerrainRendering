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
#include <exception>

#include "ResourceManager.h"

using namespace std;

MashPtr* ResourceManager::loadOBJModel(const std::string& path) {

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<GLushort> elements;

    ifstream file(path);

    if(!file.is_open()) {
        return nullptr;
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
    for (int i = 0; i < elements.size(); i+=3) {
            GLushort ia = elements[i];
            GLushort ib = elements[i+1];
            GLushort ic = elements[i+2];
            glm::vec3 normal = glm::normalize(glm::cross(
                    glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
                    glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
            normals[ia] = normals[ib] = normals[ic] = normal;
    }


    file.close();

    vector<GLfloat> vboData;
    for(int i = 0; i < vertices.size(); i++) {
        vboData.push_back(vertices[i].x);
        vboData.push_back(vertices[i].y);
        vboData.push_back(vertices[i].z);
        vboData.push_back(normals[i].x);
        vboData.push_back(normals[i].y);
        vboData.push_back(normals[i].z);
    }

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(glm::vec3), vboData.data(), GL_STATIC_DRAW);

    GLuint index_buffer = 0;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLushort), elements.data(), GL_STATIC_DRAW);

    MashPtr * mashPtr = new MashPtr(vbo, index_buffer, elements.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return mashPtr;
}

StaticModel ResourceManager::loadModel(const std::string &path) {
    MashPtr* mash = nullptr;
    auto modelElement = loadsModel.find(path);
    if(modelElement == loadsModel.end()) {
        mash = loadOBJModel(path);
        loadsModel[path] = mash;
    } else {
        mash = modelElement->second;
    }

    return StaticModel(mash);
}

ResourceManager::~ResourceManager() {

    for(auto modelMash: loadsModel) {
        delete modelMash.second;
    }

}

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager *ResourceManager::getInstance() {
    if(ResourceManager::instance == nullptr) {
        ResourceManager::instance = new ResourceManager();
    }

    return ResourceManager::instance;
}

ResourceManager::ResourceManager() { }
