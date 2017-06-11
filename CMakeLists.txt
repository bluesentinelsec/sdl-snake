cmake_minimum_required(VERSION 2.8)
project(sdl-snake C)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)

add_subdirectory(src)
