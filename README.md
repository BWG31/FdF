# FdF
Create a program to represent landscapes in 3D (Wireframe)


## Table of Contents

- [Overview](#overview)
- [Features](#features)
    - [Libc Functions](#libc-functions)
    - [Additional Functions](#additional-functions)
    - [Bonus Functions](#bonus-functions)
    - [Custom Functions](#custom-functions)
- [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Build Instructions](#build-instructions)
- [Usage](#usage)

## Overview

The objective of this project is to create a program that can interpret landscapes (provided a certain format) and create a wireframe 3D rendering of it.
This is part of the first available graphics projects at 42 and utilises the MLX (miniLibX) library that in-turn requires OpenGL and AppKit (on OSX).
- [Subject](./subject_en.pdf)
- Mark: 125/100

## TO DO
- Optimize!!! FPS drops when handling large maps or when zoom is high.
- Adjust Zoom scaling for more natural response.
- Add Camera
- Add interface indicating controls

## Features
#### Map Formatting
Maps must be formatted correctly:
    - .fdf file types
    - Must be rectangular!
    - Each number represents the altitude of any given point. It's line/column position represent the x and y axis.
    - Each point may specify a color (optional). Such a colour must be in hexadecimal RGB representation and must follow a ',' immediately after the altitude (z) value. See the povided maps in test_maps for examples.

## Installation

### Prerequisites

- GCC compiler
- MAC OS Sierra 10.2 or more recent
- miniLibX (included)
- Correctly formatted maps (included)

### Build Instructions

1. Clone the repository:
   ```sh
   git clone https://github.com/BWG31/FdF
2. Compile the library:
    ```sh
    make
3. Run the program:
    ```sh
    ./fdf <map.fdf>
4. Suggested map to try first:
    ```sh
    ./fdf test_maps/42.fdf