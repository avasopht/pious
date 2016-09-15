1. Establish device system
    * Devices may contain devices with children
    * Devices may just contain DSP
2. Platform functionality
    * UniquePtr: Swap, Release and Reset. Add Array specialization.
    * Clean up `Deleter::Destroy()` and other destruction semantics.
    * Document code on next task.
    * Create SharedPtr and WeakPtr (with array specialization).