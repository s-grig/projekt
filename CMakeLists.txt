cmake_minimum_required(VERSION 3.4)  

# Specify minimum version
set(MINIMUM_TESSERACT_VERSION 4.1.0)
set(MINIMUM_LEPTONICA_VERSION 1.74)


set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_AUTOMOC ON)

#set(Tesseract_DIR "/usr/local/lib/cmake")

#set(Leptonica_DIR "/usr/local/include")
#set(Leptonica_DIR "/home/travis/build/s-grig/projekt/leptonica-1.80.0/")

#set(Leptonica_DIR "/usr/local/lib/cmake/")
#HunterGate(
#  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
#  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"  
#)


project(projekt)


# Include subdirectories

#include("tools/gate/cmake/HunterGate.cmake")
#include_directories(/usr/include/tesseract/)
#include_directories(/usr/include/leptonica/)
# Include directories
include_directories(${Tesseract_INCLUDE_DIRS})

include_directories(${LEPTONICA_INCLUDE_DIRS})
# Check if libraries exist

find_package(SFML REQUIRED COMPONENTS system window graphics network audio)

find_package(Tesseract CONFIG REQUIRED)

find_package(Qt5Gui CONFIG REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)

find_package(Leptonica CONFIG REQUIRED)


# The main program

add_executable(main
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/ui.cpp)



target_include_directories(main
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set_target_properties(main PROPERTIES AUTOMOC TRUE)

target_link_libraries(main PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(main PUBLIC  ${Tesseract_LIBRARIES})
target_link_libraries(main PUBLIC ${Qt5Gui_LIBRARIES})
target_link_libraries(main PUBLIC ${Qt5Widgets_LIBRARIES})
target_link_libraries(main PUBLIC ${Leptonica_LIBRARIES})

#target_link_libraries(main PUBLIC -llept -ltesseract) # must add this line to link Tesseract and leptonica libs