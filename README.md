# Rotamina - Character Animator based on NanoGUI

## Installation

First, recursively clone the repository

``` bash
$ git clone --recursive https://github.com/Liby99/Rotamina.git
```

Then make a `build/` directory for the cmake to build on.

``` bash
$ mkdir build
$ cd build
```

Use CMake to create make file in the `build/` directory

``` bash
$ cmake ..
```

Then use `make` to compile the project

``` bash
$ make
```

Now all the files will be in the `test/` folder. In command line, for example, open a test file by

``` bash
$ ./test/project1/dragon_skel
```

## Example

### Skeleton

![Skeleton](https://github.com/Liby99/Rotamina/blob/master/web/public/image/skel.png?raw=true)

### Texture & Morphing

![Texture & Morphing](https://github.com/Liby99/Rotamina/blob/master/web/public/image/tex_morph.png?raw=true)
