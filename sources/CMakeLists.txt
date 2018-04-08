cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(ProtocoStateMachine CXX)

add_definitions(-DMAJOR_PROTOCOL_VERSION=4)
add_definitions(-DMINOR_PROTOCOL_VERSION=0)

option(build_tests "build tests" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("${CMAKE_SOURCE_DIR}/include")

set(
  library_sources
    src/event/ContractPrepared.cpp
    src/event/RequestPiece.cpp
    src/event/SellModeStarted.cpp
    src/event/BuyModeStarted.cpp
    src/event/Joined.cpp
    src/event/PieceLoaded.cpp
    src/event/InviteSeller.cpp
    src/event/TestSellerSpeed.cpp
    src/event/SendTestPayload.cpp
    src/exception/InvitedToJoinContractByNonBuyer.cpp
    src/exception/StateIncompatibleEvent.cpp
    src/exception/CannotInviteNonSeller.cpp
    src/exception/CannotSpeedTestNonSeller.cpp
    src/exception/SpeedTestRequestedByNonBuyer.cpp
    src/detail/InitializeBuying.cpp
    src/detail/InitializeSelling.cpp
    src/AnnouncedModeAndTerms.cpp
    src/CBStateMachine.cpp
    src/ChooseMode.cpp
    src/Active.cpp
    src/Selling.cpp
    src/Buying.cpp
    src/Observing.cpp
    src/ReadyForInvitation.cpp
    src/Invited.cpp
    src/WaitingToStart.cpp
    src/StartedSelling.cpp
    src/ServicingPieceRequests.cpp
    src/ReadyToInviteSeller.cpp
    src/WaitingForSellerToJoin.cpp
    src/SellerHasJoined.cpp
    src/PreparingContract.cpp
    src/RequestingPieces.cpp
    src/TestingSellerSpeed.cpp
    src/ReadyToSendTestPayload.cpp
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
