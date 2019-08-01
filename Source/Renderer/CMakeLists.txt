cmake_minimum_required(VERSION 3.12)
project(TerrenRenderingRenderer)

add_library(TerrenRenderingRenderer
        Shader.cpp
        Shader.h
        Camera.cpp
        Camera.h
        Renderer.cpp
        Renderer.h
        Technique.h
        Technique.cpp
        Geometry.h
        Geometry.cpp
        StaticModel.h
        StaticModel.cpp
        RenderingQueue.cpp
        RenderingQueue.h
        Terrain/QuadTree/TerrainQuadTreeManager.cpp
        Terrain/QuadTree/TerrainQuadTreeManager.h
        Terrain/QuadTree/TerrainTreeNode.cpp
        Terrain/QuadTree/TerrainTreeNode.h Texture.cpp Texture.h Terrain/TerrainTessellation/TerrainTessellationManager.cpp Terrain/TerrainTessellation/TerrainTessellationManager.h)
