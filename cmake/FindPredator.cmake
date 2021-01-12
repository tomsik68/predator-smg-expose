set(PREDATOR_DIR "${CMAKE_SOURCE_DIR}/extern/predator" CACHE STRING "Path to Predator directory(cloned from github)")
set(PREDATOR_LIBS "${PREDATOR_DIR}/cl_build/libclllvm.a" "${PREDATOR_DIR}/cl_build/libcl.a" "${PREDATOR_DIR}/sl_build/libpredator.a")
set(PREDATOR_INCLUDE_DIRS "${PREDATOR_DIR}/include/" "${PREDATOR_DIR}/cl/llvm/" "${PREDATOR_DIR}/sl/" "${PREDATOR_DIR}/cl/")

set(FAILURE_REASON "Required files not found:")

# the foreach loops are just safety check
foreach(PREDATORFILE ${PREDATOR_LIBS})
  if (NOT EXISTS ${PREDATORFILE})
    unset(PREDATOR_LIBS)
    set(FAILURE_REASON "${FAILURE_REASON},${PREDATORFILE}")
  endif()
endforeach()

foreach(PREDATORFILE ${PREDATOR_INCLUDE_DIRS})
  if (NOT EXISTS ${PREDATORFILE})
    unset(PREDATOR_INCLUDE_DIRS)
    set(FAILURE_REASON "${FAILURE_REASON},${PREDATORFILE}")
  endif()
endforeach()

# Predator's clgcc contains static variable plugName. However, clllvm does not. As a workaround, a new library is created that contains only initialization of plugName string variable. This library then must be linked to target. This is the same way as it is in predator/build-aux/common.cmake .
function(create_name_lib LIB_NAME)
  set(PLUGIN "sl")
  set(NAME_CC_FILE "${PROJECT_BINARY_DIR}/${LIB_NAME}.cc")
  file(WRITE ${NAME_CC_FILE} "#include<string>\nstd::string plugName = \"${PLUGIN}\";\n")
  add_library(${LIB_NAME} STATIC ${NAME_CC_FILE})
endfunction(create_name_lib)

create_name_lib(pluginname)
# add the library to make sure it's linked whenever Predator is linked
set(PREDATOR_LIBS ${PREDATOR_LIBS} "${PROJECT_BINARY_DIR}/libpluginname.a")
message(STATUS "predator_libs: ${PREDATOR_LIBS}")


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Predator REASON_FAILURE_MESSAGE ${FAILURE_REASON} REQUIRED_VARS PREDATOR_LIBS PREDATOR_INCLUDE_DIRS)
