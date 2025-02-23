# imageasy

`imageasy` is an image processing application that allows users to apply various effects to images. The application is built using C++, OpenGL, and ImGui for the graphical user interface.

## Features

- Load and display images
- Apply various image effects, such as blur
- Zoom in and out of images
- Modular design for easy addition of new effects

## Getting Started

### Prerequisites

To build and run `imageasy`, you need the following:

- C++ compiler with C++17 support
- CMake (version 3.15 or higher)
- Conan 2.x package manager
- OpenGL development libraries (OpenGL 4.6)

### Building

1. Clone the repository:

   ```sh
   git clone https://github.com/theweird-kid/imageasy.git
   cd imageasy
   ```

2. Install dependencies using Conan:

   ```sh
   ./run.sh install
   ```

3. Configure the project with CMake:

   ```sh
   ./run.sh configure
   ```

4. Build the project:

   ```sh
   ./run.sh build
   ```

### Running

After building the project, you can run the `imageasy` application:

```sh
./run.sh run
```
### Usage

1. Load an image using the "Load Image" tool.
2. Apply effects such as blur using the available tools.
3. Use the mouse wheel to zoom in and out of the image.
