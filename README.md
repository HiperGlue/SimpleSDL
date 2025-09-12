![Madotsuki in a witch costume](https://i.imgur.com/YPeM83X.png)

# \[C++/SDL2] HIPERGLUE'S BASIC GAME ENGINE

## What is this?

This is a basic project of a 2D game engine developed with C++ & SDL. It was made with the sole porpuse of learning the C++ language and to
avoid me the need to use a commercial game engine for my simple games.\
\

## How to set-up

This project is build using CMake and it is separated in to two modules:
+ **The engine**, which is just a static library
+ **A videogame**, only made for testing and showcasing the capabilites of the project
\
If you want to only use the engine, just get rid of the 'GAME' folders\
\

## Capabilites and components

The engine works with three simple components:
+ **Objects**, just a simple interface that tells the engine that the object needs to be included in the update loop
+ **Sprites**, basically a texture wrap around some functions and properties to allow access and modifications in its rendering
+ **Colliders**, a component with a size and position that knows and react to other colliders\

A part from these three base components, there's also a **Transform** (specifies position, rotation and size), a **Camera** (the rendering manager) and
a main class called **'Game'** which is the engine itself.

And that's basically it! Later on i'll make available the documentation.
