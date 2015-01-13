cmake_minimum_required(VERSION 2.8.4)
project(artificial_life_simulator)

# Executables.
set(SOURCE_FILES src/main.cpp)
add_executable(main ${SOURCE_FILES})

# Include directories.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Libraries.
set(EXTERNAL_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libglfw3.a pthread GL X11 Xxf86vm Xrandr Xi)


add_library(ControllerEvents ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/events.cpp)
target_link_libraries(ControllerEvents ${EXTERNAL_LIBS})

add_library(ControllerRealTimeClock ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/realtime_clock.cpp)
target_link_libraries(ControllerRealTimeClock ${EXTERNAL_LIBS})

add_library(Model ${CMAKE_CURRENT_SOURCE_DIR}/src/model/model.cpp)
target_link_libraries(Model ${EXTERNAL_LIBS})

add_library(ModelSimulationClock ${CMAKE_CURRENT_SOURCE_DIR}/src/model/simulation_clock.cpp)
target_link_libraries(ModelSimulationClock ${EXTERNAL_LIBS})

add_library(ViewWindow ${CMAKE_CURRENT_SOURCE_DIR}/src/view/window.cpp)
target_link_libraries(ViewWindow ${EXTERNAL_LIBS})

set(INTERNAL_LIBS ControllerEvents ControllerRealTimeClock Model  ModelSimulationClock ViewWindow)

target_link_libraries(main ${INTERNAL_LIBS} ${EXTERNAL_LIBS})

# Tests.
add_subdirectory(build/gmock)
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()

add_executable(unittests tests/test_clock.cpp)

target_link_libraries(unittests gmock gtest gtest_main ${INTERNAL_LIBS})
add_test(unittests unittests)

# Compile flags.
set(GCC_COMPILE_FLAGS "--std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")