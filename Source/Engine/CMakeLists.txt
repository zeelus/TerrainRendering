cmake_minimum_required(VERSION 3.12)
project(TerrenRenderingEngine)

add_library(TerrenRenderingEngine
        EngineWindow.h
        EngineWindow.cpp
        ResourceManager.h
        ResourceManager.cpp
        libs.h
        Scene.cpp
        Scene.h)

