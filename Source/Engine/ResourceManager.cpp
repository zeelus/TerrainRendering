//
// Created by Gilbert Gwizdala on 2019-01-31.
//
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    vector<glm::vec3> faceNormals;
    vector<GLushort> elements;
    vector<GLushort> elementsNormals;

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

        } else if(line.substr(0, 3) == "vn " ) {

            istringstream lineString(line.substr(3));
            glm::vec3 n;
            lineString >> n.x;
            lineString >> n.y;
            lineString >> n.z;
            faceNormals.push_back(n);

        } else if (line.substr(0, 2) == "f ") {

            auto newLine = line.substr(2);
            vector<string> strs;
            std::vector<std::string> elementsString;
            boost::algorithm::split(elementsString, newLine, boost::is_any_of(" "));

            for (auto &element: elementsString) {
                if (element.empty()) continue;

                std::vector<std::string> partString;
                boost::algorithm::split(partString, element, boost::is_any_of("/"));

                GLshort e, p, n = 0;

                if(!partString[0].empty()) {
                    e = std::stoi(partString[0]);
                }

                if(!partString[1].empty()) {
                    p = std::stoi(partString[1]);
                }

                if(!partString[2].empty()) {
                    n = std::stoi(partString[2]);
                }

                elements.push_back(--e);
                elementsNormals.push_back(--n);
            }

        }
    }

    normals.resize(vertices.size());

    for(int i = 0; i < elements.size(); i++) {
        normals[elements[i]] += faceNormals[elementsNormals[i]];
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
