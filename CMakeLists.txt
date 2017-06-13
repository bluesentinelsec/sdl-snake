cmake_minimum_required(VERSION 2.8)
project(sdl-snake C)

# cpack (`make package`)
SET(CPACK_GENERATOR "DEB")

# cpack general
SET(CPACK_PACKAGE_NAME "sdl-snake")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "Michael Hitchens <mdhitchens@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "It's Snake! Made with SDL (and SDL_mixer)! In C!")

# cpack debian
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl1.2debian (>= 1.2.15), libsdl-mixer1.2 (>= 1.2.12)")
set(CPACK_DEBIAN_PACKAGE_SECTION "games")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://44d-again-again.itch.io/sdl-snake")
set(CPACK_DEBIAN_PACKAGE_REPLACES "sdl-snake (<= 1.0.0)")

if(CPACK_GENERATOR STREQUAL "DEB")
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/images DESTINATION share/sdl-snake)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/sounds DESTINATION share/sdl-snake)
    install(FILES ${CMAKE_SOURCE_DIR}/icon.png DESTINATION share/sdl-snake)
    install(FILES ${CMAKE_SOURCE_DIR}/sdl-snake.desktop DESTINATION share/applications)
endif()

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)

add_subdirectory(src)

INCLUDE(CPack)
