# FlatLang: Declarative Language for Control Systems

FlatLang is designed with a distinct set of **core architectural principles** and **fundamental building blocks** that set it apart from traditional programming paradigms, particularly in its approach to control flow, state, and execution model.

### Core Architectural Principles of FlatLang

FlatLang is founded on a philosophy that prioritizes **pure flow, determinism, and external control**. Key principles include:

*   **Linear Flow, No Cycles**: Every node in FlatLang builds on what came before it, strictly moving forward without any internal feedback loops or self-reference. This design choice is philosophical, viewing feedback as a contradiction to the "we are the loop" concept, where the loop exists externally to the language (e.g., the user, the system, the interpreter).
*   **Stateless and Deterministic Nodes**: Each node is designed to be stateless, meaning it does not retain information between evaluations, and deterministic, ensuring the same inputs always produce the same outputs. This promotes composability and predictability.
*   **Implicit Looping through External Ticks**: FlatLang deliberately avoids explicit `for` or `while` loop constructs. Instead, looping behavior emerges naturally from the real-time (RT) tick – an external loop that drives the re-evaluation of all nodes. This means "time itself is the loop, and logic is just a reaction to it".
*   **Declarative, Not Imperative**: FlatLang describes computations as structures and transformations rather than prescribing a sequence of imperative steps. Decisions are made by the graph structure, not by jumps or control flow magic.
*   **Minimalism and Expressiveness**: The language aims to be minimal in its core syntax while remaining expressive, allowing complex behaviors to be composed from simple building blocks.

### Fundamental Building Blocks of FlatLang

The language is built upon a concise set of elements designed to support its core principles:

*   **Node Referencing**:
    *   `..`: Refers to the output of the **previous node**.
    *   `_`: Refers to the output of **all previous nodes**.
    *   `.`: Refers to the **current node's output**, but only when feedback is explicitly allowed (though FlatLang's philosophy generally avoids this).
    *   `ID`: Allows referencing **named nodes** by their label.
*   **Data Structures**:
    *   `pack`: Bundles multiple values into a single struct or list, enabling commands that conceptually take multiple arguments.
    *   `unpack`: Splits bundled values back out.
*   **Function Calls**:
    *   `call_c printf ..`: Facilitates calling **external C functions** with arguments.
*   **Constants**:
    *   `const "hello"`: Defines a **string literal**.
    *   `const 42`: Defines a **numeric literal**.
*   **Lexical Elements**:
    *   `ID`: Optional **node identifier** (e.g., `msg:`, `val:`).
    *   `OPCODE`: Represents an **operation or function name** (e.g., `const`, `pack`, `call_c`).
    *   `ARG`: An **argument**, which can be a literal, a reference (like `..`, `_`, or `ID`), or a symbol.
    *   `# COMMENT`: For **inline comments**.
*   **Node Definition**: The basic syntax for defining a node is `[ID:] OPCODE ARG1 ARG2 ... [# COMMENT]`, where `ID` is optional, `OPCODE` specifies the operation, and `ARGs` are positional inputs. This has been refined to **single-argument commands** where multiple conceptual arguments are handled via `pack`.
*   **Higher-Order Nodes (`map`, `reduce`)**: Introduced to elegantly handle iteration over data structures like buffers without traditional loops. `map` applies a subgraph to each element of a buffer, and `reduce` aggregates a buffer into a single value.
*   **Conditional Operations (`call_if`)**: Instead of `if/else` keywords, FlatLang uses a pattern of `compare` nodes followed by a `select` (or `call_if`) function. This keeps the language flat, composable, and minimal by treating conditional logic as a function call.

### Differentiation from Traditional Programming Paradigms

FlatLang differentiates itself significantly from traditional programming paradigms, particularly imperative languages, through several key aspects:

1.  **Control Flow as Functions/Structure**:
    *   **No explicit `if`, `for`, `while`**: Unlike most languages, FlatLang models conditional branching and iteration using **functions like `select` or `call_if` and dataflow structures**, rather than special keywords or control flow statements. Loops are implicitly driven by an external real-time tick, making the "loop" external to the language itself.
    *   **Higher-order functions for iteration**: `map` and `reduce` provide declarative ways to process buffers, contrasting with imperative `for` loops.

2.  **Statelessness and Immutability**:
    *   **No internal state**: Each node is stateless, promoting determinism and composability. Variables, by default, are treated as outputs of nodes, not mutable storage.
    *   **Mutation as explicit mechanism**: While the default is pure flow, explicit mechanisms like `&b` in a `pack` argument allow for **by-reference modification**, but this is a conscious design choice to support specific use cases rather than a default behavior.

3.  **Position Between Hardware Description Languages (HDLs) and Software**:
    *   **Computation Language, Not Wiring**: FlatLang is a *computation language*, describing transformations and dataflow. This differs from HDLs where "another path" often means physical hardware replication. In FlatLang, the same function graph can be reused on multiple buffers, and the runtime handles scheduling and optimization, potentially reusing compiled code.
    *   **Optimizer Reliance**: FlatLang relies heavily on its compiler/optimizer to turn its simple, declarative intent into efficient execution, especially for operations like `map_if`. The optimizer can inline, unroll, vectorize, or fuse operations, abstracting away the low-level concerns that a developer would manually manage in an HDL.

4.  **Dual-Mode Execution (Compiled vs. Realtime)**:
    *   FlatLang is envisioned to operate in two distinct modes, sharing the same syntax: a **strictly compiled mode** for embedded systems (e.g., routers, avionics) where predictability and performance are paramount, and a **realtime interpreted/JIT-compiled mode** for dynamic configuration and live tuning (e.g., adjusting landing gear parameters without recompiling the entire system). This contrasts with traditional paradigms that often commit to one execution model.

5.  **Rejection of Self-Reference/Feedback**:
    *   The philosophy explicitly states "No feedback: Because the loop is external—the user, the system, the interpreter." This prevents nodes from being dependent on themselves, maintaining the purity of the forward-moving chain. This differs from languages that freely allow recursion or self-referential data structures.

In essence, FlatLang is a **minimalist, declarative, node-based language** that models computation as a pure, forward-moving dataflow graph. It shifts the responsibility for looping and complex control from explicit language constructs to an external runtime and sophisticated compiler optimizations, making it particularly well-suited for predictable, real-time control systems and dynamic configuration.