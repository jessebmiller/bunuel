# API Versioning Automation

## Background

The Bunuel library implements extreme backwards compatibility: every function signature is versioned and frozen permanently (`bunuel_logln_v0`, `bunuel_logln_v1`, etc.). Users pin to specific API versions via `BUNUEL_PIN_API_X` macros or mix-and-match function versions.

**Current State:** Manual maintenance of `#ifdef` pin blocks and prefix stripping aliases creates significant developer friction. Adding functions or bumping API versions requires updating multiple macro blocks with mechanical, error-prone pattern replication.

**Key Insight:** The versioning rules are automatable.

## Current Condition

| Pain Point | Impact |
|------------|--------|
| **Manual macro updates** | Adding new versioned function requires updating all PIN blocks plus STRIP_PREFIX block. 3-5 edits minimum. |
| **API bump complexity** | Creating PIN_API_2 means copying PIN_API_1 block, carefully incrementing version numbers. Easy to make mistakes. |
| **Pattern replication errors** | Must find correct blocks, copy patterns, increment numbers correctly. Mechanical work prone to typos and omissions. |
| **Development hesitation** | Friction discourages adding new function versions. Better to leave it alone than risk breaking existing APIs. |

**Concrete Example:**  
Adding `bunuel_logln_v1` currently requires:
1. Add declaration in declarations section
2. Add PIN_API_1 block (maps to v1)
3. Copy rest of PIN_API_0 block in
4. Update STRIP_PREFIX block (add v1 aliases)

## Goal

Reduce API versioning friction to near-zero through automation.

**Success Criteria:**
1. Developer adds new `_vN` function declarations freely (just C code, no macro work)
2. Single `pin` command creates next API pin with all blocks regenerated correctly

**Developer Experience:**
- Add `bunuel_logln_v1()` declaration
- Keep coding, testing, iterating
- When ready to release: `pin` → done
- All macro boilerplate handled automatically

## Root Cause Analysis

**Why does this friction exist?**

1. **Multiple sources requiring sync:** Function declarations are in one place, but their API pin mappings are scattered across 3+ `#ifdef` blocks that must stay consistent.
2. **Relevant history is implicitly encoded in #ifdef blocks** This is hard to read and the rules are hard to remember.

## Countermeasures

**1. bunuel-codegen **

**Purpose:** Generate all macro blocks automatically from function declarations and existing #ifdef blocks

**Rules:**

**Rules:**
- **Non-breaking changes** (new v0 functions): Added to all existing PIN blocks automatically
- **Breaking changes** (bumped function versions): create new PIN block
  - Create new PIN_API_N+1 block
  - Copy PIN_API_N as baseline
  - Update functions to their highest available versions
- Function versions increment by exactly 1 per API (no orphaned versions)

**Output:** Updates the macro section of header file.

**Validation:**
- Bumped function versions cannot affect existing APIs
- New functions (v0) should be added to ALL existing APIs
- The diff between API N and API N+1 should only contain function version increments and additions of v0 functions 

## Follow-Up

**Key Metrics:**
- Time to generate APIs: <1 minute (target: one command)
- Manual macro errors: 0 (impossible by design)

**Success Criteria:**  
The system succeeds when developers never think about macros. Adding versioned functions feels like writing normal C code. API bumps are trivial. The extreme API stability becomes invisible infrastructure that just works.
