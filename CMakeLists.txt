cmake_minimum_required(VERSION 3.24)
project(bosconian)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-lstdc++fs -static")

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Add Bosconian dependencies
set(SDL2_INCLUDE_DIR lib/SDL2-2.26.4/include)
set(SDL2_LIB_DIR lib/SDL2-2.26.4/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR lib/SDL2_image-2.6.3/include)
set(SDL2_IMAGE_LIB_DIR lib/SDL2_image-2.6.3/lib/x64)

set(SDL2_MIXER_INCLUDE_DIR lib/SDL2_mixer-2.6.3/include)
set(SDL2_MIXER_LIB_DIR lib/SDL2_mixer-2.6.3/lib/x64)

set(SDL2_TTF_INCLUDE_DIR lib/SDL2_ttf-2.20.2/include)
set(SDL2_TTF_LIB_DIR lib/SDL2_ttf-2.20.2/lib/x64)

#set(D3D_INCLUDE_DIR lib/Direct3D/Include)
#set(D3D_LIB_DIR lib/Direct3D/Lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
link_directories(${SDL2_MIXER_LIB_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})
#include_directories(${D3D_INCLUDE_DIR})
#link_directories(${D3D_LIB_DIR})

# Add Google Tests
add_subdirectory(Google_tests)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})

add_executable(bosconian main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf) #d3d11 dxgi d3dcompiler
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})