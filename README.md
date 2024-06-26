# AbstractVideo
The Abstract Video is a cross platform low-level 3D graphics API.

## Building instruction for Linux and Max OS/X
For building the abstraction layer for Linux and Max OS/X, CMake is required. In
Linux the Vulkan headers and libraries has to be installed. The following commands
can be used for building:

```bash
mkdir build
cd build
cmake ..
make
```


# Installing bindings
### Pharo
The Pharo bindings can be installed by running the following script in a
playground:

```smalltalk
Metacello new
   baseline: 'AbstractGPU';
   repository: 'github://desromech/abstract-video/tonel';
   load
```

This installation script takes care of automatically downloading a version of
the platform specific library binary that is automatically being built on the CI
server.
