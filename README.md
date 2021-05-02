# m4c0-stl

This is a set of C++ classes I often use. They are meant to replace some C++
Standard Library (STL) classes with more specialised code, as well as add some
convenient libraries.

STL is a great library but its classes often suffer from costly compilations
and excess of heap allocations. They normally are good enough for most
projects, but it's common for me to reinvent some STL classes. After doing that
a couple of times, I decided to publish them as a open source project.

Take everything here as unstable (or, at least WIP).

## Modules

* **Core** - Convenience classes
* **DI** - Dependency injection with some scope management
* **Droid Main** - Main loop for Android apps. Uses Android's glue code, but
  this will be eventually replaced
* **Fuji** - Small Vulkan framework which provides a small overridable main 
  loop
* **iOS Main** - Main loop for Metal-based iOS apps. It does **not** sign or
  package.
* **Log** - Simple native logging. It wraps each supported platform log API in
  a minimalistic cross-platform module. Apple (iOS+OSX) uses NSLog, Windows 
  creates a file at the same directory as the executable, and Android uses its
  log library.
* **ObjC Bridge** - Hacks to inject C++ code in Obj-C
* **OSX Main** - Main loop for Metal-based OSX apps
* **Win Main** - Main loop for WIN32 apps. Eventually, `wndproc` instances will
  be injectable.
* **Maze** - Maze generation
* **Test** - Conveniences for unit tests
* **Vulkan** - Packages all Vulkan sub-libraries
* **Vulkan Actions** - Fluent interfaces for Vulkan functions (submit queue,
  etc)
* **Vulkan Commands** - Fluent interfaces for commands issued to Vulkan command
  buffers.
* **Vulkan Dynamic** - A wrapper for dynamically loading Vulkan library.
  Currently, a wrapper around Volk.
* **Vulkan Objects** - C++ wrapper for Vulkan objects. Provides RAII and fluent
  builder while adding a layer of compilation firewall for its clients.
* **Vulkan Static** - An implementation of the dynamic counterpart. This
  provides the same signature but it is compatible with static linkage. Mainly
  used in iOS/OSX to avoid codesigning MoltenVK independently.

## Third-party code

This is a list of code that is included as-is under a different license:

* `droid-main/src/glue` - distributed under the terms of the NOTICE file
  contained in that directory
