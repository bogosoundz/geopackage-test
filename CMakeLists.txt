cmake_minimum_required(VERSION 2.8.7)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

project(gdal-geopackage-test)

file(GLOB sources
    "headers/*.h"
    "sources/*.cpp"
)

add_executable(main-test ${sources})
include_directories("/opt/gdal-trunk/include/" headers)
target_link_libraries(main-test /opt/gdal-trunk/lib/libgdal.so)
