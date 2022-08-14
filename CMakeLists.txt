cmake_minimum_required(VERSION 3.20)
project(LidarMesh)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

## Find dependencies
find_package(glfw3 REQUIRED)
# find_package(glm REQUIRED)
# find_package(freetype REQUIRED)
# find_package(imgui REQUIRED)

# stb does not have a CMake build, but is header-only
# find_path(STB_INCLUDE_DIRS "stb.h") 

# Dear ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_library(IMGUI STATIC)

target_sources( IMGUI
                PRIVATE
                    ${IMGUI_DIR}/imgui_demo.cpp
                    ${IMGUI_DIR}/imgui.h
                    ${IMGUI_DIR}/imgui.cpp
                    ${IMGUI_DIR}/imgui_draw.cpp
                    ${IMGUI_DIR}/imgui_tables.cpp
                    ${IMGUI_DIR}/imgui_widgets.cpp
                    ${IMGUI_DIR}/imstb_rectpack.h
                    ${IMGUI_DIR}/imstb_textedit.h
                    ${IMGUI_DIR}/imstb_truetype.h

                PRIVATE
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.h
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h
                    ${IMGUI_DIR}/backends/imgui_impl_glfw.h
                    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp


                )

target_include_directories( IMGUI
                            PUBLIC ${IMGUI_DIR}
                            PUBLIC ${IMGUI_DIR}/backends
                            PUBLIC ${SDL2_DIR}/include
                            )

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

## Create main executable
add_executable(main src/main.cpp
)

target_include_directories(main 
  PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(
  main
  PRIVATE
    glfw
    IMGUI 
    ${OPENGL_LIBRARIES}
)