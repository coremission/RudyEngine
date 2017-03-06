cmake_minimum_required(VERSION 2.8)

set(GLFW_SOURCE_DIR "external/glfw")
set(GLM_SOURCE_DIR  "external/glm")
set(GLAD_SOURCE_DIR "external/glad")
set(ASSIMP_SOURCE_DIR "external/assimp")
set(GLI_SOURCE_DIR "external/gli")

# Building only the GLFW lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

add_subdirectory(${GLFW_SOURCE_DIR})
add_subdirectory(${ASSIMP_SOURCE_DIR})

include_directories(${GLAD_SOURCE_DIR}/include
                    ${GLFW_SOURCE_DIR}/include
                    ${GLFW_SOURCE_DIR}/deps
                    ${GLM_SOURCE_DIR}
                    ${GLI_SOURCE_DIR}
                    ${ASSIMP_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/engine)

add_library(glad STATIC ${GLAD_SOURCE_DIR}/src/glad.c)

####################################
############ RudyEngine ############
####################################
set(RUDY_MODEL_SOURCES Model/Component.cpp Model/GameObject.cpp Model/ModelLoader.cpp Model/Scene.cpp Model/Transform.cpp Model/VertexData.cpp)
set(RUDY_RENDERING_SOURCES Rendering/BaseRenderer.cpp Rendering/Camera.cpp Rendering/Mesh.cpp Rendering/MeshManager.cpp Rendering/rendering.cpp Rendering/ShaderLoader.cpp Rendering/SkyboxRenderer.cpp
    Rendering/Sprite.cpp Rendering/SpriteRenderer.cpp Rendering/Texture.cpp Rendering/TextureManager.cpp Rendering/WireframeRenderer.cpp)

add_library(engine
            Application.cpp
            rudymath.cpp
            ${RUDY_MODEL_SOURCES}
            ${RUDY_RENDERING_SOURCES})

SET_TARGET_PROPERTIES(engine PROPERTIES COMPILE_FLAGS "-std=c++14")
target_link_libraries(engine glfw ${GLFW_LIBRARIES} glad assimp)
