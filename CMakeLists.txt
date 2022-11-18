cmake_minimum_required(VERSION 3.20)
project(LidarMesh)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

## Find dependencies
find_package(glfw3 REQUIRED) #This is drop in replacement for opengGL
find_package(glad REQUIRED) 
find_package(glm REQUIRED)
# find_package(imgui REQUIRED)

# Dear ImGui (This static lib setup is done most places)
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

# opengl (Dont know why this is required and it kinda bugs things out)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})


# ADDING CGAL LIBRARIES
set(CGAL_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/input)
find_package(CGAL REQUIRED)
# find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

# # Boost and its components
find_package(Boost REQUIRED)


if(NOT Boost_FOUND)
  message(
    STATUS
      "NOTICE: This project requires the Boost library, and will not be compiled."
  )
  return()
endif()


find_package(Eigen3 3.1.0 REQUIRED) #(requires 3.1.0 or greater)
include(CGAL_Eigen3_support)
if(NOT TARGET CGAL::Eigen3_support)
  message(
    STATUS
      "NOTICE: This project requires Eigen 3.1 (or greater) and will not be compiled."
  )
  return()
endif()


set(GLPK_INCLUDE_DIR "C:/depends/glpk-4.35/include")
set(GLPK_LIBRARIES "C:/depends/glpk-4.35/w64/glpk.lib")

find_package(GLPK QUIET)
include(CGAL_GLPK_support)
if(NOT TARGET CGAL::GLPK_support)
  message(
    STATUS
      "NOTICE: This project requires either SCIP or GLPK, and will not be compiled."
  )
  return()
endif()

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCE_STUFF RELATIVE ${SOURCE} CONFIGURE_DEPENDS "*.h" "*.cpp")
## Create main executable
# add_executable(main src/main.cpp ${SOURCE_STUFF})
add_executable(main src/main.cpp 
  # src/cgal.cpp
  # src/cgal.h
  src/backend.cpp
  src/backend.h
)

target_include_directories(main 
  PRIVATE 
  SOURCE
)
target_link_libraries(
  main
  PRIVATE
    glfw
    glad::glad
    glm::glm
    IMGUI 
    ${OPENGL_LIBRARIES}
    CGAL::CGAL
CGAL::Eigen3_support
CGAL::GLPK_support
)


# target_link_libraries( main PUBLIC CGAL::Eigen3_support)
# # # target_link_libraries( PUBLIC CGAL::CGAL_Basic_viewer)
# target_link_libraries( main PUBLIC CGAL::GLPK_support)