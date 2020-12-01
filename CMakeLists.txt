cmake_minimum_required(VERSION 3.4)    

set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_AUTOMOC ON)

#include("tools/gate/cmake/HunterGate.cmake")

#HunterGate(
#  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
#  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"  
#)

project(kp)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)

	message("-- Building <${PROJECT}> for <${CMAKE_CXX_COMPILER_ID}> compiler")
	add_definitions(/W4)

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)

	message("Building <${PROJECT}> for <${CMAKE_CXX_COMPILER_ID}> compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.7")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)

	message("-- Building <${PROJECT}> for <${CMAKE_CXX_COMPILER_ID}> compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)

	message("-- Building <${PROJECT}> for <${CMAKE_CXX_COMPILER_ID}> compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

else ()

	message(FATAL_ERROR "<${PROJECT}> Unknown compiler")

endif ()




find_package(SFML REQUIRED COMPONENTS system window graphics network)

find_package(Tesseract CONFIG REQUIRED)

find_package(Qt5Gui CONFIG REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)

#-DCMAKE_TOOLCHAIN_FILE=C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake

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

