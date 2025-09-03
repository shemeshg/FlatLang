# FlatLang: Declarative Language for Control Systems

** Tempporary project, might be removed **

FlatLang will be a declarative configuration language designed for real-time control systems. It models logic as a graph of symbolic operations—such as comparisons, conditionals, and modular arithmetic—mapped to hardware bindings or internal virtual state.

FlatLang will be:
- Stateless and order-agnostic
- Designed for strict compile-time evaluation, with optional runtime hooks
- Expressive enough to describe embedded logic, yet minimal enough to remain readable
- Built in C++ with Python bindings via pybind11

It will supports:
- External hardware bindings (e.g. GPIO, clock signals)
- Semantic grouping of inputs and outputs
- Aliases for symbolic clarity
- Function templates with parameterized logic
- Optional debug output via virtual buffers

FlatLang will be ideal for systems where clarity, determinism, and modularity matter—from microcontrollers to future quantum logic simulations.



