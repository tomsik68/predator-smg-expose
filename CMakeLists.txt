cmake_minimum_required(VERSION 3.1)
project(smgexpose C CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(LLVM_LIBS all)

find_package(Predator REQUIRED)

add_executable(smgexpose_test src/smgexpose_test.cpp src/PredatorInterface.cpp)

set_target_properties(smgexpose_test PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    #LINK_FLAGS "-Wl,--entry=plugin_init"
)

add_compile_options(-Wall -Wextra -pedantic)

target_include_directories(smgexpose_test PRIVATE include/ ${PREDATOR_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})
target_link_libraries(smgexpose_test PRIVATE ${LLVM_LIBS} ${PREDATOR_LIBS})
