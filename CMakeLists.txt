cmake_minimum_required(VERSION 3.1..3.18)
project(smgexpose C CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(LLVM_LIBS all)

find_package(Predator REQUIRED)
find_package(Passes REQUIRED)

add_executable(smgexpose_test src/PredatorInterface.cpp src/smgexpose_test.cpp)

target_compile_features(smgexpose_test PRIVATE cxx_std_14)
set_target_properties(smgexpose_test PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(smgexpose_test PRIVATE -Wall -Wextra -pedantic -fno-rtti -g)

target_include_directories(smgexpose_test PRIVATE SYSTEM ${PASSES_INCLUDE_DIRS} ${PREDATOR_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})
target_include_directories(smgexpose_test PRIVATE include/)
target_link_libraries(smgexpose_test PRIVATE ${LLVM_LIBS} ${PREDATOR_LIBS} ${PASSES_LIBS})
