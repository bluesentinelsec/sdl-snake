SDL SNAKE
=========

It's Snake! Made with SDL (and SDL_mixer)! In C!

Requirements
------------

  * cmake 2.8+
  * A C compiler
  * SDL 1.2
  * SDL_mixer 1.2

Compilation (General)
---------------------

The general idea is something like this:

```
cmake .
make
```

However, some OSes need a bit of tweaking...

Compilation (Windows)
---------------------

First, the `SDLDIR` environment variable must point to the base SDL directory.
This is the directory that contains `lib` and `include`.

```
SET SDLDIR=<path to SDL directory>
```

Then run CMake, then compile whatever spits out.

Running
-------

```
./sdl-snake
```

Controls
--------

  * Arrow keys to move
  * Enter key to select
  
Game Notes
----------

  * EASY is the slowest snake; each food gives 1 point
  * NORM is a faster snake; each food gives 2 points
  * HARD is the fastest snake; each food gives 4 points

License
-------

Everything in this project I'ved licensed under the _Do What the Fuck You
Want to Public License_. You can find it in the `LICENSE` file, or from the
WTFPL website:

```
www.wtfpl.net
```