//
// Created by Gilbert Gwizdala on 2019-01-31.
//
#include <glbinding/gl/gl.h>
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
#include <optional>

#include "ResourceManager.h"
#include "../Renderer/Shader.h"

using namespace std;

ResourceManager::ResourceManager() { }

optional<Geometry> ResourceManager::loadOBJModel(const std::string& path) {

    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec3> faceNormals;
    vector<GLushort> elements;
    vector<GLushort> elementsNormals;

    ifstream file(path);

    if(!file.is_open()) {
        return {};
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

                GLushort e, p, n = 0;

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

    vector<glm::vec3> vboData;
    for(int i = 0; i < vertices.size(); i++) {
		vboData.push_back(vertices[i]);
		vboData.push_back(normals[i]);
    }

    gl::GLuint vao = 0;
	gl::glGenVertexArrays(1, &vao);
	gl::glBindVertexArray(vao);

		gl::GLuint vbo = 0;
		gl::glGenBuffers(1, &vbo);
		gl::glEnableVertexAttribArray(vertex_position_location);
		gl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
		gl::glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(glm::vec3), vboData.data(), GL_STATIC_DRAW);
		gl::glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

		gl::glEnableVertexAttribArray(vertex_normal_location);
		gl::glVertexAttribPointer(vertex_normal_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

		gl::GLuint index_buffer = 0;
		gl::glGenBuffers(1, &index_buffer);
		gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLushort), elements.data(), GL_STATIC_DRAW);

	gl::glBindVertexArray(0u);

	gl::glBindBuffer(GL_ARRAY_BUFFER, 0u);
	gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

    return Geometry(vao, vbo, index_buffer, static_cast<unsigned int>(elements.size()), getIndexTechnique(TechniqueType::PhongBline));
}

const int ResourceManager::loadModel(const std::string &path) {
    int index = -1;
    auto modelIndexInVector = modelIndexs.find(path);
    if(modelIndexInVector == modelIndexs.end()) {

        optional<Geometry> modelMashOpt = loadOBJModel(path);
        if(modelMashOpt) {
            Geometry modelMash = *modelMashOpt;
            loadsModel.push_back(modelMash);
            index = static_cast<int>(loadsModel.size() - 1);
            modelIndexs[path] = index;
        }

    } else {
        index = modelIndexInVector->second;
    }

    return index;
}


ResourceManager* ResourceManager::instance = nullptr;

ResourceManager *ResourceManager::getInstance() {
    if(ResourceManager::instance == nullptr) {
        ResourceManager::instance = new ResourceManager();
        ResourceManager::instance->loadTechniques();
    }

    return ResourceManager::instance;
}

void ResourceManager::loadTechniques() {

    Shader vertex(Vertex, "Resources/Shaders/VertexShader.vert");
    Shader fragment(Fragment, "Resources/Shaders/FragmentShader.frag");
    this->loadsTechnique.emplace_back(vertex, fragment);

}

const Technique& ResourceManager::loadTechnique(const unsigned int index) const {
    return this->loadsTechnique[index];
}

const Geometry& ResourceManager::getGeometry(const unsigned int index) const {
    return loadsModel[index];
}

constexpr short ResourceManager::getIndexTechnique(TechniqueType techniqueType) {
    switch (techniqueType) {
        case TechniqueType::PhongBline:
            return 0;
        default:
            return -1;
    }
}


