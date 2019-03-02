set(glbinding_FOUND "NO")
set(glbinding_INCLUDE_DIRS "NOTFOUND")
set(glbinding_LIBRARIES "NOTFOUND")

if(WIN32 AND NOT UNIX)
    set(glbinding_LIBRARIES_OPT optimized "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/Win/${CONFIGURATION_TYPE}/x64/glbinding.lib" optimized "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/Win/${CONFIGURATION_TYPE}/x64/glbinding-aux.lib")
    set(glbinding_LIBRARIES_DEBUG debug "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/Win/${CONFIGURATION_TYPE}/x64/glbindingd.lib" debug "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/Win/${CONFIGURATION_TYPE}/x64/glbinding-auxd.lib")

    set(glbinding_INCLUDE_DIRS "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/include")

    set(glbinding_FOUND "YES")
else()
    if(NOT APPLE)
        set(glbinding_LIBRARIES_OPT optimized "${TerrenRendering_SOURCE_DIR}/../Libs/glbinding/lib/Linux/linux64/libglbinding.a" optimized "${TerrenRendering_SOURCE_DIR}/../Libs/glbinding/lib/Linux/linux64/libglbinding-aux.a")
        set(glbinding_LIBRARIES_DEBUG debug "${TerrenRendering_SOURCE_DIR}/../Libs/glbinding/lib/Linux/linux64/libglbinding.a" debug "${TerrenRendering_SOURCE_DIR}/../Libs/glbinding/lib/Linux/linux64/libglbinding-aux.a")

        set(glbinding_INCLUDE_DIRS "${TerrenRendering_SOURCE_DIR}/../Libs/glbinding/include")

        set(glbinding_FOUND "YES")
    else()
        set(glbinding_LIBRARIES_OPT optimized "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/macOS/libglbinding.dylib" optimized "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/macOS/libglbinding-aux.dylib")
        set(glbinding_LIBRARIES_DEBUG debug "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/macOS/libglbinding.dylib" debug "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/lib/macOS/libglbinding-aux.dylib")

        set(glbinding_INCLUDE_DIRS "${TerrenRendering_SOURCE_DIR}/Libs/glbinding/include")

        set(glbinding_FOUND "YES")

    endif()
endif()

set(glbinding_LIBRARIES ${glbinding_LIBRARIES_OPT} ${glbinding_LIBRARIES_DEBUG})

message("glbinding found: ${glbinding_FOUND}")
message("glbinding include dir: ${glbinding_INCLUDE_DIRS}")
message("glbinding libraries: ${glbinding_LIBRARIES}")
