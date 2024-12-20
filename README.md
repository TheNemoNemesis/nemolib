# NEMOLIB
This library is a thin wrapper around SDL3 and Dear Imgui.
It's aimed at making C++ windowing and GUI development easier.

## Contents
- [Download](#Download) 
    - [Releases](#releases) 
    - [Build from source](#build) 
- [Usage](#Usage) 
- [Todo](#Todo) 

## Download
The NemoLib library can be obtained in multiple ways.
#### releases
You can download the library files from the [releases](https://github.com/TheNemoNemesis/nemolib/releases) page.
Than extract the compresed archive and copy the files to the desired directory.\
*example:*
```bash
tar -xvf nemolib_linux_x86-64.tar.gz --directory ./nemolib
cp nemolib/include ~/includes/nemolib
cp nemolib/libnemolib.a ~/libs/libnemolib.a
```
#### build
You can also build the library from the source. The library requires for SDL3 and relative dependencies to be
installed in your system. You would also need cmake and make to build the project with the CMakeLists.txt file.\
*example:*
```bash
git clone --recursive https://github.com/TheNemoNemesis/nemolib
cd nemolib
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

## Usage


## Todo
- [ ] Better readme with examples
- [ ] Rendering functions inside window object
- [ ] Fix autoloop bugs
- [ ] Custom imgui widgets
