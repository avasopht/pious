Emcee: a locally scoped general purpose C++ library
===================================================

Emcee is a general purpose library for C++ for environments where the following
are prohibited:

1. No access to `malloc`, `calloc`, `free`, `new` and `delete`.
    * You have access to a block of memory, but you manage it yourself.
2. No access to statically scoped variables.
    * This means you can't make use of much of stl.



What Emcee provides
-------------------

1. Memory management abstraction interface with `malloc()`, `free()`, `new()`, etc.
2. Smart pointers (`unique_ptr`, `shared_ptr`, etc.)
3. A basic containers (`vector`, etc.)
4. Smart auto-injection
    * Containers inject a pointer to the `memory` object into newly created
      objects.

See the following example of array creation and destruction:
 
    Type *array = emcee::New<Type[10]>(mem).Create(default_value);
    assert(emcee::ArraySize(array) == 10);
    emcee::Delete(array);

