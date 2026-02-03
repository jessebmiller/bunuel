# A3 Problem Solving: Bunuel Traceability Matrix System

## Background

The Bunuel library maintains multiple API versions simultaneously (PIN_API_0, PIN_API_1, etc.), each with different function versions. 

**Current State:** No systematic way to track which requirements exist in which API versions, whether they're tested, or what changed between versions. Documentation is manual and often incomplete.

**Goal:** Link documentation, tests, and implementations across all API versions, expose missing pieces.

## Current Condition

| Pain Point | Impact |
|------------|--------|
| **No test coverage tracking** | Don't know if PIN_API_0 has all tests passing. Could unknowingly break old API versions. |
| **Opaque version differences** | Users asking "what changed in PIN_API_2?" requires manual inspection of header diffs. |
| **No coverage gaps detection** | Can't detect when a function, requirement, or test exists but has no corresponding elements. |

**Concrete Example:**  
Developer adds `bunuel_arena_wipe_v1` with new semantics. Questions that can't be easily answered:
- Does this satisfy an existing requirement or is it new functionality?
- Which tests validate the v1 behavior vs v0 behavior?
- Where is this functionality documented, and tested?

## Goal

Visibility into requirements, tests, and implementations across all API versions for library developers and users.

**Success Criteria:**
1. Every function version traceable to specific requirements and tests
2. Automated detection of coverage gaps (requirement without test, test without requirement, implementation without test)
3. One command generates complete version comparison matrix
4. One command validates all API pins have full test coverage

**Developer Experience:**
- Add new requirement: system flags if no test/implementation exists
- Add new test: system shows which requirements it validates

## Root Cause Analysis

**Why doesn't this exist?**
1. **No structured metadata:** Requirements and test coverage exist in developers' heads or scattered comments, not in queryable form.
2. **No linking mechanism:** No formal way to link a test to the requirement it validates or the implementation it exercises.
3. **Manual validation:** Checking test coverage requires manually reading tests and implementations. Time-consuming and error-prone.
4. **Version complexity:** With multiple API pins, need to track "this requirement exists in PIN_API_2+ but not PIN_API_0-1" - too complex to manage manually.

## Countermeasures

**1. Traceability Metadata Format**

Defines links to and from tests, implementations, and requirements.

**Structured lines:** define links to other elements ad hoc in single lines
```c
// TRACE: implements ARENA_002
void* bunuel_bump_arena_v0(bunuel_Arena_v0* arena);
```

```c
// TRACE: tests ARENA_003
void test_bunuel_bump_arena_at_cap_v0() { ... }
```

```md
## Arena Requirements (v0)

- TRACE: requirement **ARENA_001:** Arenas should be wipeable
- TRACE: requirement **ARENA_002:** Arenas should be bumpable
- TRACE: requirement **ARENA_003:** arena bump returns NULL when at capacity
```

**Tooling**
- Generate manifest or db. Reports complete, missing, and broken links
- Insert backlinks ("implemented by" from "implements" etc.)
- Shows linked items side by side so you can see the requirements, implementation and tests in one view to validate

**Core Commands:**
```bash
# Validate coverage
$ bunuel trace validate
✓ [53/55] requirements have implementations
✓ [55/55] implementations have tests
✗ ARENA_015 missing tests
✗ test_pool_concurrent has no linked requirement
✗ 12 instances of unknown code

# Inspect linked items
$ bunuel trace show ARENA_015

Requirement docs/logging.md:56
Logln adds a newline to the end of the formatted log

Implementation lib.h:6
int logln(char *fmt, ...);

Implementation lib.c:23
int logln(char *fmt, ...) {
    ...
    putchar('\n');
    ...
}

Test MISSING
```

**Success Criteria:**  
The system succeeds when:
- Developers quickly discover when they add code without linking it to requirements/tests (and vice versa)
- Release validation catches missing test coverage before users see it
- The traceability matrix becomes the source of truth for "what's in which API version"

## Future work

- Version aware tracing

