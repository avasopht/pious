Pious: Polyphonic I/O Unit System
=================================

Pious is a cross-platform polyphonic audio DSP processing and device routing
framework written in [C] that also includes a plugin API with the following
features:

1. Target multiple platforms with a single code base (include Rack Extensions and VST).
2. Design new devices from existing plugins using a modular device builder.
3. Design polyphonic synthesizers capable of being extended by user effects!

We are in early stages of development so here is what to expect.

Pious v0.0.1 Road Map
---------------------

1. I can define a module with audio, cv and midi inputs and outputs.
2. I can connect a module to the MASTER interface.
3. I can connect, disconnect and reconnect a module to the environment audio interface.
4. I can connect a chain of modules together and manually schedule the programming
5. I can create a module processing queue
6. I can generate a module processing queue
7. I can create a monophonic composite module
8. I can create a polyphonic composite module
9. I can route between monophonic and polyphonic submodules
10. Module state is managed and can be saved and reloaded
0. I can load modules from a plugin


Cross platform
--------------

Writing to this framework allows you to target [VSTs],
[Rack Extensions] and [Audio Units] with a single codebase, while also being
able to support future platforms without a single change in code so long as
it is compatible with a modest C/C++ subset and uses the API to access assets
and manage device state.

Pious is in early stages of development but will eventually provide
standardized methods for accessing file assets from a database, managing
device state and taking care of undo while providing a mechanism for DAWs
undo integration.

Create devices with internal wiring
-----------------------------------

Inspired by the [Reason Combinator], Pious allows you to create a new device
by connecting units together. This allows you to create new devices by
connecting old devices together.

The device routing mechanism simplifies the creation of regular devices
by allowing you to focus on writing algorithms and connecting them together.
This allows quick and easy experimentation, and a live suite in the future
will allow you to do this in real time to allow yourself and designers to
create new devices, synthesizers and effects through rapid experimentation.

Auto-delay compensation can be calculated within the devices using this system
so that you can report back plugin delay in response to what's actually going
on inside your plugin, plus it will allow internal plugin delay compensation
when needed.

Did I forget to mention polyphonic!
-----------------------------------

Pious allows you to create a polyphonic device with ease. Your polyphonic
voice banks can still input and output monophonic data, and on top of that
you will also be able have your polyphonic section output multi channel
audio and MIDI / control messages. Imagine that! allowing your synth to
dynamically output to multiple audio channels.

Real time device routing
------------------------

Pious gives you the power to alter your device routing in real time. Want to
provide users with custom routing options? Sure, go ahead, Pious will happily
reconnect the internal devices and adjust auto-delay compensation while it's
at it.

Intuitive platform independent GUI development in the works
-----------------------------------------------------------

We want to simplify the development process greatly while being able to
support current and future environments. We cannot predict the future entirely
but we do at least know that 4K monitors are getting cheaper and cheaper,
while more and more people are beginning to utilize the power of mobile
devices and tablets, so our coming GUI framework will help facilitate that.

Inspired by the [Rack Extension] SDK, Pious will offer a 3d modelling
framework for people that way inclined as well as some new UI innovations.

Licensing
---------

Unless otherwise stated, all source files are licensed under the MIT license.

    MIT License

    Copyright (c) 2016 The Pious Authors

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

[C]: http://www.cprogramming.com/
[Rack Extension]: https://www.propellerheads.se/reason/rack-extensions
[Rack Extensions]: https://www.propellerheads.se/reason/rack-extensions
[VSTs]: https://www.steinberg.net/en/products/vst.html
[Audio Units]: https://en.wikipedia.org/wiki/Audio_Units
[Reason Combinator]: https://www.propellerheads.se/reason/instruments/combinator