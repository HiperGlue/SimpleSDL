# SIMPLESDL: A BASIC 2D ENGINE

![Madotsuki in a witch costume](https://i.imgur.com/ifysW4J.png)

## What is this?

This is a basic **2D game engine** developed with **C++ & SDL**. It was made with the sole porpuse of learning the C++ language and to
avoid me the need of using a commercial one for my simple games.\

This project focuses on avoid OOP and prefer composition while simplifying the structure of the engine.

## How to use

This project is build using CMake and compiled as an static library.\
In order to use it just include the .lib/.a file and the include folder into your project

## Capabilites and components

The engine works with, basically, three simple components:
+ **Objects**: Just a simple interface that tells the engine that the object needs to be included in the update loop
+ **Sprites**: A texture wrap around inside a class with some functions and properties to allow modifications in its rendering
+ **Colliders**: A shape with size and position that knows and react to other colliders

Apart from these three basic components, there's also a **Transform** (specifies position, rotation and size), a **Camera** (the rendering manager) and
a main class called **'Game'** which is the engine itself that manages all the processes internally.

And that's basically it!\
Later on i'll make available the documentation.
