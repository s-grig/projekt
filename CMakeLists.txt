cmake_minimum_required(VERSION 3.4)  

# Specify minimum version
set(MINIMUM_TESSERACT_VERSION 4.1.0)
set(MINIMUM_LEPTONICA_VERSION 1.74)


set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_AUTOMOC ON)


#HunterGate(
#  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
#  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"  
#)

set(PROJECT_NAME "KP")
project(${PROJECT_NAME} CXX)


# Include subdirectories
#include("file/tessdata/eng.traineddata")
#include("tools/gate/cmake/HunterGate.cmake")

# Include directories
include_directories(${Tesseract_INCLUDE_DIRS})     # you

# Check if libraries exist

find_package(SFML REQUIRED COMPONENTS system window graphics network)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
#find_package(Leptonica CONFIG REQUIRED)
##find_package(Tesseract CONFIG REQUIRED)
find_package(Tesseract REQUIRED) # 4.1.1 is currently the latest version of the git repository.


# The main program

add_executable(main
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/ui.cpp)


target_include_directories(main
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set_target_properties(main PROPERTIES AUTOMOC TRUE)


target_link_libraries(main PRIVATE ${Tesseract_LIBRARIES})

target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-network)

target_link_libraries(main PRIVATE ${Qt5Gui_LIBRARIES})

target_link_libraries(main PRIVATE ${Qt5Widgets_LIBRARIES})


