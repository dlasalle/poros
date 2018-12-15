Poros
=====

<a href="https://travis-ci.org/dlasalle/poros">
  <img src="https://travis-ci.org/dlasalle/poros.svg?branch=master"/>
</a>


A C++ graph partitioning library implementing the [Metis](cs.umn.edu/~metis)
recursive bisection algorithm.


Requirements
------------

To compile Poros you will need `CMake` >= 2.8 and a C++ compiler supporting
`c++14`.

The `configure` script is currently written in `bash`, but `cmake` can be
invoked directly to build the library.


Building
--------

To just build the dynamic library execute:
```
./configure && make
```

and `build/<os-arch>/src/libporos.so` will be built.


To build the static library

```
./configure --static && make
```

and `build/<os-arch>/src/libporos.a` will be built.


Testing
-------

To compile and run the unit tests, execute:

To just build the dynamic library execute:
```
./configure --test && make && make test
```


