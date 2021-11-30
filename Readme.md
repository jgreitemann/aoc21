Advent of Code 2021
===================

Building
--------

This repository uses CMake as a project model and Conan.io for dependency management. With both of those installed, you
can build it as follows:

```bash
$ mkdir build && cd build
$ conan install ..
$ cmake ..
$ cmake --build .
```

Authentication
--------------

With Advent of Code, the puzzle input is different for every user. This program will download yours automatically as
needed, caching it in your temp directory. In order to authenticate yourself, go
to [adventofcode.com](https://adventofcode.com/), log in with whatever service you're using.

Next, find your session cookie. For instance, in Firefox, you can right-click the website anywhere, choose _Inspect_,
select the _Storage_ tab, select _Cookies → https://adventofcode.com_ from the tree view on the left-hand-side, and copy
the value of the cookie named `session`. Set this cookie (a long hex string) as an environment variable `SESSION`:

```bash
$ export SESSION=8badf00d...
```
