# Pious Road Map

## v0.0.1 User Stories / features

1. _(done)_ Callback function for devices
2. I can connect a module to the MASTER interface.
    * The MASTER interface could be connected to a VST interface, an Audio
      Interface or just be being rendered for use in another plugin_!
    * Connecting the module will make use of a C++ routing library (eventually
      AudioTK after prototyping).
3. I can connect, disconnect and reconnect a module to the environment audio interface.
4. I can connect a chain of modules together and manually schedule the programming
5. I can create a module processing queue
6. I can generate a module processing queue
7. I can create a monophonic composite module
8. I can create a polyphonic composite module
9. I can route between monophonic and polyphonic submodules
10. Module state is managed and can be saved and reloaded

## Future User Stories

1. Modules can reference modules compiled as plugins