cmake_minimum_required(VERSION 3.28.1)
set (CMAKE_CXX_STANDARD 23)

project(RayTracer VERSION 0.1.0 LANGUAGES C CXX)

set(HEADERS
    include/color.h
    include/ray.h
    include/sphere.h
    include/surface.h
    include/vec3d.h
    include/math_utils.h
    include/surface_list.h
    include/interval.h
    include/camera.h
    include/material.h
)

set(SOURCE
    src/main.cpp
    src/sphere.cpp
    src/surface_list.cpp
    src/interval.cpp
    src/camera.cpp
    src/material.cpp
)

add_executable(RayTracer ${HEADERS} ${SOURCE})
target_include_directories(RayTracer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
