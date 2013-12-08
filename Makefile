build:
	mkdir -p build
	cp -r images build
	cp -r sounds build
	gcc src/* -o build/sdl-snake -I/usr/include/SDL -lSDL -lSDL_mixer

clean:
	rm -r -f build

.PHONY: build clean