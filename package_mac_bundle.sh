#!/bin/bash

# Make macOS packaging a shell script because I can't get cpack to do what I want
#
# Make sure you install beforehand, and that SDL and SDL_mixer are in
# ~/Library/Frameworks

set -e

# Clean
rm -rf dist-mac

mkdir -p dist-mac
cd dist-mac

# Make bundle structure
mkdir -p sdl-snake.app/Contents/MacOS
mkdir -p sdl-snake.app/Contents/Frameworks
mkdir -p sdl-snake.app/Contents/Resources

# Copy everything into place
cp ../Info.plist sdl-snake.app/Contents

cp ../build/src/sdl-snake sdl-snake.app/Contents/MacOS

cp -R ../images sdl-snake.app/Contents/Resources/
cp -R ../sounds sdl-snake.app/Contents/Resources/

cp -R ~/Library/Frameworks/SDL.framework sdl-snake.app/Contents/Frameworks/
cp -R ~/Library/Frameworks/SDL_mixer.framework sdl-snake.app/Contents/Frameworks/

cp ../README.txt .

mkdir -p Licenses
cp ../COPYING-SDL-MIXER.txt Licenses
cp ../COPYING-SDL.txt Licenses
cp ../README-SDL.txt Licenses

# (Icons need more work)
iconutil -c icns -o sdl-snake.app/Contents/Resources/sdl-snake.icns ../sdl-snake.iconset

# Naively delete all rpaths
for rpath in `otool -l sdl-snake.app/Contents/MacOS/sdl-snake | grep "path " | awk '{ print $2 }'`
do
    install_name_tool -delete_rpath "$rpath" sdl-snake.app/Contents/MacOS/sdl-snake
done

# Set up new rpaths
install_name_tool -add_rpath "@loader_path/../Frameworks" sdl-snake.app/Contents/MacOS/sdl-snake

# Create a dmg
cd ..
hdiutil create -volname sdl-snake -srcfolder dist-mac/ -ov -format UDZO sdl-snake.dmg
