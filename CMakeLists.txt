cmake_minimum_required(VERSION 3.20)
project(LidarMesh)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

## Find dependencies
find_package(glfw3 REQUIRED)
# find_package(glad REQUIRED)
# find_package(glm REQUIRED)
# find_package(freetype REQUIRED)
# find_package(imgui REQUIRED)

# stb does not have a CMake build, but is header-only
# find_path(STB_INCLUDE_DIRS "stb.h") 

# Dear ImGui
set(IMGUI_DIR ../../)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends )

## Create main executable
add_executable(main src/main.cpp)
target_include_directories(main 
  PRIVATE 
    # ${STB_INCLUDE_DIRS}
    "${CMAKE_CURRENT_LIST_DIR}/src"
    ${IMGUI_DIR}
)
target_link_libraries(
  main
  PRIVATE
    # freetype
    glfw
    # glad::glad
    # glm::glm
)