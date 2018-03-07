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

Now all the test executable files will be in the `test/` folder. Note that there are extra CMake
files in `test` folder. They will be executed for copying all the relevant files for that test set.
In command line, for example, open a test file by

``` bash
$ cd test/animation
$ ./char_anim_viewer
```

## Example

### Skeleton

![Skeleton](https://github.com/Liby99/Rotamina/blob/master/doc/images/skel.png?raw=true)

### Texture & Morphing

![Texture & Morphing](https://github.com/Liby99/Rotamina/blob/master/doc/images/tex_morph.png?raw=true)

### Animation

![Animation](https://github.com/Liby99/Rotamina/blob/master/doc/images/animation.png?raw=true)

### Cloth Simulation

![Cloth](https://github.com/Liby99/Rotamina/blob/master/doc/images/flag.png?raw=true)

### Inverse Kinematics

![IK](https://github.com/Liby99/Rotamina/blob/master/doc/images/ik_2.png?raw=true)
