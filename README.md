# System Explorer

## Dependency Installation

### macOS

    $ brew install glew

    $ brew install glfw3

    $ brew install glm

    $ brew install freetype

### Windows

Download [https://sourceforge.net/projects/glew/files/glew/1.13.0/](glew-1.13.0-win32.zip).

Extract the `glew-1.13.0` directory to `vendor\glew-1.13.0`.

Download [https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.bin.WIN64.zip](glfw-3.2.1.bin.WIN64.zip).

Extract the `glfw-3.2.1.bin.WIN64` directory to `vendor\glfw-3.2.1.bin.WIN64`.

Initialize the glm git submodule:

    $ git submodule update --init --recursive
