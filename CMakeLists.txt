cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(ProtocoStateMachine CXX)

option(build_tests "build tests" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("${CMAKE_SOURCE_DIR}/include")

set(
  library_sources
    src/*.cpp
    src/detail/*.cpp
    src/event/*.cpp
    src/exception/*.cpp
)

# === build library ===
add_library(protocol_statemachine ${library_sources})

# === build tests ===
if(build_tests)
  set(
    test_common_sources
      test/BuyingNavigator.cpp
      test/CBStateMachineCallbackSpy.cpp
      test/SellingNavigator.cpp
  )

  # === test library ===
  include_directories("${CMAKE_SOURCE_DIR}/test")

  add_library(test_common ${test_common_sources})

  file(GLOB tests RELATIVE "${CMAKE_SOURCE_DIR}" "test/test_*.cpp")

  enable_testing()

  foreach(s ${tests})
    get_filename_component (sn ${s} NAME_WE)
    add_executable(${sn} ${s})
    target_link_libraries(${sn} test_common protocol_statemachine ${CONAN_LIBS})
    add_test(${sn} "bin/${sn}")
  endforeach(s)

endif()
