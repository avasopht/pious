# Limitations for code in the library and API

The Pious library and API aims to be able to execute in an environment
that is quite restricted, so all code within the library must also
adhere to the listed limitations.

## No static scope

All variables must either be held on stack or as class members. This
includes the use of static variables in functions.

A workaround in the `Os` class will be provided.

## No system memory allocation or deletion during the host's rendering method.

This means no calls to `malloc()`, `free()`, `new` (without placement)
and `delete` (for any object created without placement).
 
To get around this limitation the library includes `Allocate()` and
`Free()` methods in the `Os` class.

This limitation means that the Standard Template Library (and the use
of many other libraries such as Boost's Smart Pointers) are
inaccessible.

Custom alternatives may be provided in the future.

## No direct access to the Operating System

No direct access to the operating system for opening files, creating
threads, reading data or accessing the network interface.

## No assumptions to be made about floating point implementation

For safety sake floats must be treated like black boxes.

[Rack Extension]: https://www.propellerheads.se/reason/rack-extensions