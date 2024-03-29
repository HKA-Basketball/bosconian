cmake_minimum_required(VERSION 3.24)

# 'Google_test' is the subproject name
project(Google_tests)

set(GOOGLETEST_VERSION 1.13.0)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SDL2_INCLUDE_DIR ../lib/SDL2-2.26.4/include)
set(SDL2_LIB_DIR ../lib/SDL2-2.26.4/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR ../lib/SDL2_image-2.6.3/include)
set(SDL2_IMAGE_LIB_DIR ../lib/SDL2_image-2.6.3/lib/x64)

set(SDL2_MIXER_INCLUDE_DIR ../lib/SDL2_mixer-2.6.3/include)
set(SDL2_MIXER_LIB_DIR ../lib/SDL2_mixer-2.6.3/lib/x64)

set(SDL2_TTF_INCLUDE_DIR ../lib/SDL2_ttf-2.20.2/include)
set(SDL2_TTF_LIB_DIR ../lib/SDL2_ttf-2.20.2/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
link_directories(${SDL2_MIXER_LIB_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp are source files with tests
add_executable(Google_Tests_run main.cpp utilities_test.cpp physics_test.cpp

        ../src/Utilities/Math.cpp ../src/Utilities/Math.h
        ../src/Utilities/Random.cpp ../src/Utilities/Random.h
        ../src/Utilities/Vector2D.h
        ../src/Utilities/Degree.cpp ../src/Utilities/Degree.h
        ../src/Utilities/Config.h
        ../src/Model/World.h

        # For physics test
        ../src/Physics/Hitbox.cpp ../src/Physics/Hitbox.h
        ../src/Physics/HitboxManager.cpp ../src/Physics/HitboxManager.h
)

# Link Google Test libraries and SDL2 libraries
target_link_libraries(Google_Tests_run gtest gtest_main)

# Link SDL2 libraries (order matters)
target_link_libraries(Google_Tests_run SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf)