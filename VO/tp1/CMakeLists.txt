project(vpAsservissementVisuel)
cmake_minimum_required(VERSION 2.8)
find_package(VISP REQUIRED)
include_directories(${VISP_INCLUDE_DIRS})
add_executable(vpAsservissementVisuel vpAsservissementVisuel.cpp)
target_link_libraries(vpAsservissementVisuel ${VISP_LIBRARIES})