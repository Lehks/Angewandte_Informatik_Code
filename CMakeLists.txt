cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(Seminar_Angewandte_Informatik)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("deps/glfw")

add_library("glad" STATIC "deps/glad/src/glad.c")
target_include_directories("glad" PUBLIC "deps/glad/include")

add_executable("opengl-example" "src/main.c" "src/util.c")
target_include_directories("opengl-example" PUBLIC "include")
target_link_libraries("opengl-example" PRIVATE "glad")
target_link_libraries("opengl-example" PRIVATE "glfw")

configure_file("shader/example_shader.vs.glsl" "shader/example_shader.vs.glsl")
configure_file("shader/example_shader.fs.glsl" "shader/example_shader.fs.glsl")
