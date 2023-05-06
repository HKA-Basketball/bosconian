cmake_minimum_required(VERSION 3.24)
project(bosconian)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

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

add_executable(bosconian main.cpp src/Renderer/Window.cpp src/Renderer/Window.h src/Renderer/Renderer.cpp src/Renderer/Renderer.h Resources/fonts.h Resources/imgs.h src/Event/EventManager.cpp src/Event/EventManager.h src/Utilities/Vector2D.h src/Sound/SoundManager.cpp src/Sound/SoundManager.h src/Game/World.cpp src/Game/World.h src/Game/RayTrace.cpp src/Game/RayTrace.h src/Drawing/Graphics.cpp src/Drawing/Graphics.h src/Drawing/Image.cpp src/Drawing/Image.h includes.h src/Utilities/Logging.cpp src/Utilities/Logging.h src/Utilities/GlobalVars.cpp src/Utilities/GlobalVars.h src/Game/Entity.cpp src/Game/Entity.h src/Game/Projectile.cpp src/Game/Projectile.h src/Game/Hitbox.cpp src/Game/Hitbox.h src/Game/Player.cpp src/Game/Player.h src/Game/Game.cpp src/Game/Game.h src/Utilities/Initializer.cpp src/Utilities/Initializer.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf) #d3d11 dxgi d3dcompiler
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})