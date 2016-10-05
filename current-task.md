1. Establish device system
    * Devices may contain devices with children
    * Devices may just contain DSP
2. Platform functionality
    * UniquePtr: Swap, Destroy and Reset. Add Array specialization. (done)
    * Clean up `Deleter::Destroy()` and other destruction semantics. (done)
    * Document code on next task.
    * Create SharedPtr and WeakPtr (with array specialization).