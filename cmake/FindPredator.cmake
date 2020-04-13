set(PREDATOR_DIR "${CMAKE_SOURCE_DIR}/extern/predator" CACHE STRING "Path to Predator directory(cloned from github)")
set(PREDATOR_LIBS "${PREDATOR_DIR}/cl_build/libclllvm.a" "${PREDATOR_DIR}/sl_build/libpredator.a")
set(PREDATOR_INCLUDE_DIRS "${PREDATOR_DIR}/include/")

set(FAILURE_REASON "Required files not found:")

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

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Predator FAIL_MESSAGE REASON_FAILURE_MESSAGE ${FAILURE_REASON} REQUIRED_VARS PREDATOR_LIBS PREDATOR_INCLUDE_DIRS)
