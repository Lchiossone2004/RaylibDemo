#!/bin/bash

# Compiler options
CXX=g++
CXXFLAGS="-Iinclude -Wall -Wextra -std=c++17"
LDFLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"

# Create build directory if it doesn't exist
mkdir -p build

# Compile each source file into an object file
$CXX $CXXFLAGS -c src/Game.cpp -o build/Game.o
$CXX $CXXFLAGS -c src/SetUp.cpp -o build/SetUp.o
$CXX $CXXFLAGS -c src/ColisionMap.cpp -o build/ColisionMap.o
$CXX $CXXFLAGS -c src/Gameplay.cpp -o build/Gameplay.o
$CXX $CXXFLAGS -c src/Player.cpp -o build/Player.o
$CXX $CXXFLAGS -c src/Enemy.cpp -o build/Enemy.o
$CXX $CXXFLAGS -c src/Character.cpp -o build/Character.o
$CXX $CXXFLAGS -c src/Sword.cpp -o build/Sword.o

# Link object files into a single executable
$CXX build/*.o -o build/Game $LDFLAGS

# Run the game
./build/Game

# Clean up executable after running
rm -f ./build/Game

