//
// Created by Gilbert Gwizdala on 2019-07-30.
//

#include "TerrainTessellationManager.h"
#include "glbinding/gl/gl.h"
#include "../../../Engine/ResourceManager.h"

TerrainTessellationManager::TerrainTessellationManager(): textureIndex(ResourceManager::getInstance()->loadTexture("Resources/Texture/Heightmap.dds")) {

    this->init();

}

void TerrainTessellationManager::init() {

    auto model = make_plane(10u, 10u);

    gl::GLuint vao = 0;
    gl::glGenVertexArrays(1, &vao);
    gl::glBindVertexArray(vao);

    gl::GLuint vbo = 0;
    gl::glGenBuffers(1, &vbo);
    gl::glEnableVertexAttribArray(vertex_position_location);
    gl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl::glBufferData(GL_ARRAY_BUFFER, model.first.size() * sizeof(glm::vec3), model.first.data(), GL_STATIC_DRAW);
    gl::glVertexAttribPointer(vertex_position_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    gl::GLuint index_buffer = 0;
    gl::glGenBuffers(1, &index_buffer);
    gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.second.size() * sizeof(GLushort), model.second.data(), GL_STATIC_DRAW);

    gl::glBindVertexArray(0u);

    gl::glBindBuffer(GL_ARRAY_BUFFER, 0u);
    gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);


    auto geometry = Geometry("TerrainModel", vbo, index_buffer, static_cast<unsigned int>(model.second.size()), 3,
                             RenderingType::Plane, vao);

    int geometryIndex = ResourceManager::getInstance()->setGeometry(geometry);

    staticModel = new StaticModel(geometryIndex);

    staticModel->scale(glm::vec3(20.0, 1.0, 20.0));
}

std::pair<std::vector<glm::vec3>, std::vector<GLushort>>
TerrainTessellationManager::make_plane(const int dX, const int dZ) const {
    std::vector<glm::vec3> vertecs;// = {glm::vec3(0,0,0), glm::vec3(0,0,1), glm::vec3(1,0,0), glm::vec3(1,0,1)};
//    //std::vector<GLushort> elements = {0, 1, 2, 1, 3, 2};
    std::vector<GLushort> elements;// = {0, 1, 2, 3};

    const double diX = 1.0 / dX;
    const double diZ = 1.0 / dZ;

    for(unsigned int x = 0; x < dX; x++) {
        for(unsigned int y = 0; y < dZ; y++) {
            const double startX = x * diX;
            const double startZ = y * diZ;

            vertecs.emplace_back(glm::vec3(startX, 0, startZ));
            vertecs.emplace_back(glm::vec3(startX + diX, 0, startZ));
            vertecs.emplace_back(glm::vec3(startX, 0, startZ + diZ));
            vertecs.emplace_back(glm::vec3(startX + diX, 0, startZ + diZ));
        }
    }

    int number = 0;
    for(auto& vertex: vertecs) {
        elements.push_back(number);
        number++;
    }

    return std::pair(vertecs, elements);
}

TerrainTessellationManager::~TerrainTessellationManager() {
    delete this->staticModel;
}

void TerrainTessellationManager::drowIn(const Renderer &renderer) const {
    gl::glPatchParameteri(GL_PATCH_VERTICES, 4u);
    renderer.drawStaticModel(this->staticModel->getIndexGeometryIndex(), this->staticModel->getTransform(), textureIndex);
}
