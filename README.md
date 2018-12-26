Poros
=====

<a href="https://travis-ci.org/dlasalle/poros">
  <img src="https://travis-ci.org/dlasalle/poros.svg?branch=master"/>
</a>

<a href="https://ci.appveyor.com/project/dlasalle/poros">
  <img src="https://ci.appveyor.com/api/projects/status/63qae2yj658w41dr/branch/master?svg=true" />
</a>

<a href='https://poros.readthedocs.io/en/latest/poros_8h.html'>
  <img src='https://readthedocs.org/projects/poros/badge/?version=latest' alt='Documentation Status' />
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

A command line front-end is available in the
[poros-bin](https://github.com/dlasalle/poros-bin) repository.


Testing
-------

To compile and run the unit tests, execute:

To just build the dynamic library execute:
```
./configure --test && make && make test
```


