---
layout: default
title: Using Engine with your project
---

Engine has been built and tested on macOS and Linux. (I'd like some help getting it working on Windows, if you have the time and inclination!)

Engine also depends upon the CMake build system, and the Conan dependency manager.

## Installing dependencies with Conan

Engine is available from (and makes use of the) the [Conan](https://www.conan.io) dependency manager. And so should you. It's pretty good.

To incorporate Engine into your project using Conan, create a file called `conanfile.txt`, and add the following:

```
[requires]
engine/{{ site.version }}@DEGoodmanWilson/stable
```

If you are using [more advanced Conan features](http://docs.conan.io/en/latest/conanfile_py.html), you can just add this to your `conanfile.py`

```python
class MyAwesomeProject(ConanFile)
    requires = "engine/{{ site.version }}@DEGoodmanWilson/stable"
    ...
```

At any rate, _from your build directory_, simply run

```bash
$ conan install --build=missing path/to/source
```

(The `--build=missing` is because at the moment Engine only offers source installs&emdash;we'll offer pre-built binaries before too long, just you see.)

(You can read more about using Conan with your project [in the Conan docs](http://docs.conan.io/en/latest/))

### Conan options

You can fiddle with the following options for your build:
 
* `build_shared_libs` Build Engine as a dynamic/shared library. Default is to build as a static library. Building shared libraries is basically untested at the moment.

The following options exist, but only really affect development of Engine

* `build_engine_tests` Build the Engine test suite. Default is not to.
* `build_engine_examples` Build the included Engine example projects. Default is not to.
* `build_engine_coverage` Build the Engine coverage suite. Implies `build_engine_tests=True`. Default is not to.

## CMake

If you've never used Conan before, it works with a wide range of project toolchains, but Conan works best with CMake. Add the following lines somewhere near the top of your `CMakeLists.txt`:

```cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
```

Then you can run CMake as usual

```bash
cmake path/to/source
cmake --build .
```