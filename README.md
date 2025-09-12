# \[C++/SDL2] HIPERGLUE'S BASIC GAME ENGINE

![Madotsuki in a witch costume](https://i.imgur.com/ifysW4J.png)

## What is this?

This is a basic project of a __2D game engine__ developed with **C++** & **SDL**. It was made with the sole porpuse of learning the C++ language and to
avoid me the need of using a commercial one for my simple games.

## How to use

This project is build using CMake and it is separated into two modules:
+ **The engine**, which is just a static library
+ **A videogame**, only made for testing and showcasing the capabilites of the engine

If you want to only use the engine, just get rid of the 'GAME' folders in the project

## Capabilites and components

The engine works with, basically, three simple components:
+ **Objects**: Just a simple interface that tells the engine that the object needs to be included in the update loop
+ **Sprites**: A texture wrap around inside a class with some functions and properties to allow modifications in its rendering
+ **Colliders**: A shape with size and position that knows and react to other colliders

Apart from these three basic components, there's also a **Transform** (specifies position, rotation and size), a **Camera** (the rendering manager) and
a main class called **'Game'** which is the engine itself that manages all the processes internally.

And that's basically it!\
Later on i'll make available the documentation.
