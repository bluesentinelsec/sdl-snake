# SDL SNAKE

It's Snake! Made with SDL (and SDL_mixer)! In C!

## Requirements

  * CMake 2.8+
  * A C compiler
  * SDL 1.2
  * SDL_mixer 1.2

## Compilation (General)

The general idea is something like this:

```
mkdir build
cd build
cmake ..
make
```

Some platforms need more work than others, though...

### Compilation (Windows)

First, the `SDLDIR` environment variable must point to the base SDL directory.
This is the directory that contains `lib` and `include`.

```
SET SDLDIR=<path to SDL directory>
```

Then run CMake. Then compile whatever CMake spits out.

You'll need to copy all the SDL and SDL_mixer DLLs to the EXE directory. Don't
worry; it will remind you if you haven't when you run the EXE :)

## Running

```
./build/srcsdl-snake
```

or on Windows

```
build\src\sdl-snake.exe
```

## Distributing

### .deb

To create a .deb (assuming you have compiled):

```
make package
```

This will create `build/sdl-snake-X.Y.Z-Linux.deb`.

### .dmg

Assuming you have compiled and are running on macOS:

```
./package_mac_bundle.sh
```

This will create `dist-mac/` and turn its contents into `sdl-snake.dmg`

## Gameplay

### Controls

  * Arrow keys to move
  * Enter key to select

### Notes

  * EASY is the slowest snake; each food gives 1 point
  * NORM is a faster snake; each food gives 2 points
  * HARD is the fastest snake; each food gives 4 points

## License

MIT; see `LICENSE`
