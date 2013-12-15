cmake_minimum_required(VERSION 2.8)
project(sdl-snake C)

file(GLOB sources "src/*.c")
add_executable(sdl-snake ${sources})

message(STATUS "Finding SDL 1.2 dev libs")
find_package(SDL)
if (SDL_FOUND)
    message(STATUS "Finding SDL 1.2 dev libs - found")
    include_directories(${SDL_INCLUDE_DIR})
    target_link_libraries(sdl-snake ${SDL_LIBRARY})
else (SDL_FOUND)
    message(FATAL_ERROR "Finding SDL 1.2 dev libs - NOT FOUND")
endif (SDL_FOUND)

# NOTE: version 2.8.7 uses SDLMIXER_INCLUDE_DIR and SDLMIXER_LIBRARY
# NOTE: version 2.8.12 uses SDL_MIXER_INCLUDE_DIRS and SDL_MIXER_LIBRARIES
message(STATUS "Finding SDL_mixer 1.2 dev libs")
find_package(SDL_mixer)
if (SDLMIXER_FOUND)
    message(STATUS "Finding SDL_mixer 1.2 dev libs - found")
    include_directories(${SDLMIXER_INCLUDE_DIR})
    target_link_libraries(sdl-snake ${SDLMIXER_LIBRARY})
else (SDLMIXER_FOUND)
    message(FATAL_ERROR "Finding SDL_mixer 1.2 dev libs - NOT FOUND")
endif (SDLMIXER_FOUND)
