cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(smgexpose VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Predator REQUIRED)

add_executable(smgexpose_test src/smgexpose_test.cpp)
target_include_directories(smgexpose_test PRIVATE include/)
target_include_directories(smgexpose_test PRIVATE ${PREDATOR_INCLUDE_DIRS})
target_link_libraries(smgexpose_test PRIVATE ${PREDATOR_LIBS})