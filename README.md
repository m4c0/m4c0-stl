# m4c0-stl

This is a set of C++ classes I often use. They are meant to replace some C++
Standard Library (STL) classes with more specialised code, as well as add some
convenient libraries.

STL is a great library but its classes often suffer from costly compilations
and excess of heap allocations. They normally are good enough for most
projects, but it's common for me to reinvent some STL classes. After doing that
a couple of times, I decided to publish them as a open source project.

## Modules

* **Core** - Convenience classes
* **DI** - Dependency injection with some scope management
* **Log** - Simple native logging. It wraps each supported platform log API in
  a minimalistic cross-platform module. Apple (iOS+OSX) uses NSLog, Windows 
  creates a file at the same directory as the executable, and Android uses its
  log library.
* **Test** - Conveniences for unit tests

