cmake_minimum_required(VERSION 2.8)
project(SLAM_VIEWER)
set(DEBUG OFF)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

MESSAGE(STATUS "Compiling on Unix")

ADD_DEFINITIONS(-DPANGOLIN)

if(DEBUG)
    ADD_DEFINITIONS(-ggdb)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -O3 -march=native ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native -std=c++11")

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(OpenCV 3.0 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 2.4.3 REQUIRED)
endif()
find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${EIGEN3_INCLUDE_DIR}
)

include_directories(${Pangolin_INCLUDE_DIRS})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# Set SLAM Viewer sourcefiles
LIST(APPEND SOURCEFILES
    # SLAM Viewer system
    src/Config.cc
    src/Map.cc
    src/MapPoint.cc
    src/KeyFrame.cc
  
    # UI
    src/ui/MapDrawer.cc
    src/ui/Viewer.cc
)

add_library(${PROJECT_NAME} SHARED ${SOURCEFILES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Pangolin_LIBRARIES})

# Build examples
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(Viewer src/SLAM_Viewer.cc)
target_link_libraries(Viewer ${PROJECT_NAME})
