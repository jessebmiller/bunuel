## A3: Capability-Driven API Management

### Background

The Bunuel library maintains extreme backwards compatibility by permanently
freezing function signatures (e.g., `bunuel_logln_v0`, `bunuel_logln_v1`).
Specific pinnable versions are made available via manual `#ifdef` blocks in
`bunuel.h`. As the library grows, we need a way to handle not just versioning (v1, v2, v3),
but also platform-specific backends (SDL3 vs. Win32) and performance
characteristics (fast, small, realtime) and specific feature options (utf8,
audio, 3d, secp256k1) without a combinatorial explosion of
manual code.

**Current State:**

* **Manual Maintenance:** Adding a single function version requires 3-5 manual
  edits across `BUNUEL_PIN_API_X` and `BUNUEL_STRIP_PREFIX` blocks.
* **Opaque Implementation:** There is no easy way to swap a "standard"
  implementation for a "realtime" or "unicode" one while keeping the API
  stable.

### Problem Statement

The current manual versioning system is high-friction and discourages the
addition of new specialized function versions. It lacks a mechanism to resolve
which specific implementation should be linked when multiple "capabilities"
(like platform, encoding, or speed) overlap with a frozen API version.

### Root Cause Analysis

1. **Implicit History:** The relationship between API pins and implementations
is hidden inside nested macros.
2. **Lack of Dispatch:** There is no "matchmaker" to connect a generic user
call (e.g., `logln()`) to a specific implementation based on build-time
requirements (e.g., `unicode` + `v4`).

### Countermeasures: The Capability Registry

We will transition to a model where versions and specialized implementations
are metadata-driven, using the `pin` tool as a logic engine.

**1. Source Annotations (The Source of Truth):** Instead of a separate DSL, use
`@` tags in headers/source to define what a function version provides.

* `@name`: The generic API name (e.g., `bunuel_Str`).
* `@version`: The specific implementation version (e.g., `v4`).
* `@caps`: Capabilities provided (e.g., `unicode`, `fast`).
* `@pin`: Which API versions this version becomes the "default" for.

**2. Automated "Matchmaker" Codegen:** The `pin` tool scans these annotations
and generates the combinatorial `#ifdef` logic in `bunuel.h`.

* **Natural Versioning:** Use version numbers (`v0`, `v1`, `v2`) to
  differentiate implementations.
* **Capability Gating:** If a user defines `BUNUEL_WANT_UNICODE`, the
  `pin`-generated logic redirects `bunuel_Str` to the version that provides
  that capability (e.g., `v4`), even if the API pin's default was `v3`.

**3. Implementation Stability:** Keep internal function names simple (e.g.,
`bunuel_Str_v4`). Do not bake the entire capability list into the C symbol
name. Use the `pin` tool to handle the "invisible infrastructure" of mapping.

### Implementation Plan

| Task | Description | | --- | --- | | **Standardize Tags** | Define the
`@name`, `@version`, and `@caps` syntax in `lib.h` files. | | **`pin` Tool
Logic** | Create a script to parse these tags and build a capability-to-version
matrix. | | **Update `bunuel.h**` | Replace manual `#ifdef` blocks with a
`GENERATED START/END` block managed by the `pin` tool. |

### Success Criteria

* **Zero manual macro edits:** Adding a new capability or version requires only
  a source comment.
* **Stable User Code:** Users can switch from `ASCII` to `UNICODE` by changing
  a build flag, without changing their function calls.
* **Traceability:** The `rtm` tool can use these same `@caps` tags to validate
  requirement coverage.

