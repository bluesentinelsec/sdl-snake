set(sources
	crash.c
	deb_mem.c
	difficulty.c
	game.c
	game_structs.c
	input.c
	list.c
	menu.c
	score.c
	sdl_snake.c
	sprite_strip.c
	stage.c
	transition.c
)

if(APPLE)
	set(sources ${sources} SDLMain.m)
endif()

add_executable(
	sdl-snake
	${sources}
)

target_link_libraries(
	sdl-snake
	${SDL_LIBRARY}
	${SDLMIXER_LIBRARY}
)

target_include_directories(
	sdl-snake
	PRIVATE ${SDL_INCLUDE_DIR}
	PRIVATE ${SDLMIXER_INCLUDE_DIR}
)

install(TARGETS sdl-snake DESTINATION bin)
