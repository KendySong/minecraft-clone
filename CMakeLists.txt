cmake_minimum_required (VERSION 3.23)
project (minecraft-clone)

file (GLOB_RECURSE SOURCE 
    src/*.cpp
    libraries/ImGui/*.cpp
    libraries/glad/src/*.c
    libraries/stb/*.cpp
)

add_executable (${PROJECT_NAME} ${SOURCE})

include_directories (
    libraries
    include
    include/application
    include/render
    include/world
)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC libraries/glfw/include 
    PUBLIC libraries/glad/include 
    PUBLIC libraries/glm
)

target_link_directories(${PROJECT_NAME}
    PUBLIC libraries/glfw 
    PUBLIC libraries/glad 
    PUBLIC libraries/glm
)

target_link_libraries(${PROJECT_NAME} 
    glfw
    glm
)