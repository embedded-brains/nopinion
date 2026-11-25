<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

# AGENTS.md

nopinion reads the machine code of SPARC ELF files and reports the
instruction sequences of hardware errata of Gaisler LEON processors. The
specification drives the code. Each behaviour has a requirement item below
`spec/nopinion/`, and the tests are generated from the items.

## Build and test

| Target | What it does |
| --- | --- |
| `make check` | builds the program and the validation test program, then runs the tests |
| `make coverage` | runs the tests with `--coverage` and fails below 100% lines or branches |
| `make generate SPEC_VENV=<venv>` | regenerates `tests/tc-*.c` and `tests/ts-nopinion.c` from the items |

`make generate` needs a Python environment with specware and the `rtems`
repository as a sibling directory. `specitems.yml` loads `../rtems/spec`
for the glossary, the reference items and the item types.

Run `make check` and `make coverage` before each commit. Run
`uvx reuse lint` after you add a file.

## Change a behaviour

The item is the source. The generated test follows it.

1. Read the errata document or the technical note of the erratum. The
   SPARC Architecture Manual Version 8 gives the instruction formats.
2. Write or change the plain requirement. It links to the document with
   the role `reference` and names the section in `location`.
3. Write or change the action requirement which refines it. Its transition
   map covers every combination of the pre-condition states.
4. Name a new test target in `spec/build/nopinion/validation.yml`. The
   export refuses a target which the build item does not name.
5. Run `make generate`, then change the C code until `make check` passes.
6. Reach 100% coverage with states of the items.

Write each check from the documents of the vendor alone. Treat the Gaisler
scan scripts as a black box. Run them to compare reports, and keep their
code out of this repository and out of your context.

A branch which no input reaches is a defect of the code. Remove it, and
keep the gcovr exclusion markers out of the sources.

An item which cites a document needs its reference item. `spec/ref/` holds
copies of reference items of `rtems`. A copy keeps the UID and the content
of the `rtems` item.

## Code map

| Concept | Where |
| --- | --- |
| ELF files and `ar` archives | `src/elf.c` |
| instruction classes as flags | `src/decode.c`, flags `F_*` in `src/nopinion.h` |
| the flow through delay slots, annulled slots and branch targets | `src/flow.c` |
| sequence checks over a path of the flow | the table `sequence_checks` in `src/flow.c` |
| checks of one instruction and its neighbours | the dispatch in `check_section()` |
| one unit per erratum | `src/tn00*.c`, `src/asi1c.c`, `src/powerdown.c` |
| the report line, the SARIF log of `-f sarif`, `-v`, `-q`, `-s` | `src/report.c` |
| the options and the part table of `-p` | `src/cli.c` |
| the test support, hand-written | `tests/tx-support.c`, `tests/tx-wrap.c` |

A finding is *definite* when the instructions decide it. It is *possible*
when it needs an unknown instruction. The end of a section and a relocated
target are unknown. With `-i`, the target of JMPL, RETT and trap always is
unknown as well. Other tools
read the report line, so its form belongs to the specification.

## Item pitfalls

- YAML 1.1 reads the state names `On`, `Off`, `Yes` and `No` as booleans.
  The review tools then crash. Name such states `Included` and `Excluded`.
- A pre-condition after the end of the code section takes the state `N/A`
  in the transition map, as in `check-tn-0016-stfsr.yml`.

## Commits

Follow `CONTRIBUTING.md`. A message takes the form of Conventional Commits
with a sentence-case subject. The `Assisted-by:` trailer of the assistant
stands directly before `Signed-off-by:`. The person who certifies the DCO
signs off.
