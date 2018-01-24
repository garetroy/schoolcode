cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(main)
SET(VTK_DIR /home/users/groberts/uoregon-parallel/projects/Rasterizer/VTK-6.3.0)
SET(CMAKE_CXX_FLAGS "-fopenmp")

file(GLOB SRCFILES
    "*.h"
    "*.cxx"
)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(main ${SRCFILES} main)

if(VTK_LIBRARIES)
  target_link_libraries(main ${VTK_LIBRARIES})
else()
  target_link_libraries(main vtkHybrid)
endif()

