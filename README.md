# Bouncing Ball Simulation
A simple simulation of balls bouncing in a window, made in OpenGL

## Inspiration
The project is inspired and based on [this](https://www.vobarian.com/collisions/2dcollisions2.pdf) PDF document. Please, check it out, since it's quite interesting.

## Build
Make sure to initalize the project's submodules before building:
    
    git submodule init
    git submodule update

Build using CMake. Execute the commands from inside the project's root directory.

    mkdir build && cd build
    cmake -G<generator> ..
    <command for your generator>

Recommended generators are Ninja (ninja) and make.
The binary will be output in the bin directory in the build directory.

## Usage
Run the executable from the binary directory, so that it can read the vertex and fragment shader files.

## Visuals
![](readme/program.png "Program")
