//
// Created by Gilbert Gwizdala on 2019-07-30.
//

#include "TerrainTessellationManager.h"
#include "glbinding/gl/gl.h"
#include "../../../Engine/ResourceManager.h"

TerrainTessellationManager::TerrainTessellationManager(float screenWidth, float screenHeight, float lodFactor, const int textureIndex)
        : screenWidth(screenWidth), screenHeight(screenHeight), lodFactor(lodFactor), textureIndex(textureIndex) {

    init();
    initUBO();
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


    auto geometry = Geometry("TerrainModel", vbo, index_buffer, static_cast<unsigned int>(model.second.size()), 2,
                             RenderingType::Plane, vao);

    int geometryIndex = ResourceManager::getInstance()->setGeometry(geometry);

    staticModel = new StaticModel(geometryIndex);

    staticModel->scale(glm::vec3(20.0, 2.0, 20.0));
    staticModel->setPosition(glm::vec3(-0.5, 0.0, -0.5));
}

std::pair<std::vector<glm::vec3>, std::vector<GLushort>>
TerrainTessellationManager::make_plane(const int dX, const int dZ) const {
    std::vector<glm::vec3> vertecs;
    std::vector<GLushort> elements;

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

void TerrainTessellationManager::drowIn(Renderer &renderer) const {
    gl::glPatchParameteri(GL_PATCH_VERTICES, 4u);
    renderer.setUboTerrainTessellationHandle(ubo_terrain_tessellation_handle);
    renderer.drawStaticModel(this->staticModel->getIndexGeometryIndex(), this->staticModel->getTransform(), textureIndex);
    renderer.setUboTerrainTessellationHandle(0);
}

void TerrainTessellationManager::initUBO() {
    gl::glGenBuffers(1, &ubo_terrain_tessellation_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_terrain_tessellation_handle);
    std::array<glm::vec4, 1u> light = { glm::vec4(screenWidth, screenHeight, lodFactor, 0.0f) };
    gl::glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), light.data(), gl::GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0u);
}


