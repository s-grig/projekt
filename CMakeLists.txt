cmake_minimum_required(VERSION 3.4)    

set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(KP_VERSION_MAJOR 1)
set(KP_VERSION_MINOR 0)
set(KP_VERSION_PATCH 1)
set(KP_VERSION
${KP_VERSION_MAJOR}.${KP_VERSION_MINOR}.${KP_VERSION_PATCH}.${KP_VERSION_TWEAK})
set(KP_VERSION_STRING "v${KP_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include("tools/gate/cmake/HunterGate.cmake")
#include(CPackConfig.cmake)

#HunterGate(
#  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
#  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"  
#)

project(kp)
#cmake -DCMAKE_TOOLCHAIN_FILE=c:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake ...
find_package(SFML REQUIRED COMPONENTS system window graphics network audio)

find_package(Tesseract CONFIG REQUIRED)

#-DCMAKE_TOOLCHAIN_FILE=C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake

add_executable(main
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)

target_include_directories(main
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(main PRIVATE libtesseract)

target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

