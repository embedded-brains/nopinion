<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

## Submitting issues

Please submit issues through
[GitHub nopinion issues](https://github.com/embedded-brains/nopinion/issues).
A false finding or a missed sequence needs the instruction words. The option
`-v` prints them.

## Contributing to the project

### Specification first

Each behaviour of nopinion has a requirement item below `spec/nopinion/`.
A check follows the text of the errata document or the technical note and
the SPARC Architecture Manual Version 8. Cite the document and its section
in the item. Write the item before you change the code.

Contribute no code of the Gaisler errata scan scripts. A comparison of the
reports of both tools is welcome.

### C development guidelines

The code is C11 for a POSIX host. Format it with `clang-format` and the
`.clang-format` file of the repository. The build uses the warnings of the
`WARNINGS` variable of the `Makefile`. A contribution adds no warning.

### Tests

The test cases in `tests/tc-*.c` are generated from the action
requirements. Change the item and run `make generate` instead of an edit
of a generated file. Run `make check` to run the tests. Keep the line
coverage and the branch coverage of `make coverage` at 100%. A branch
which no input reaches is a defect. Remove it instead of an exclusion.

Each file carries an SPDX license line or an entry in `REUSE.toml`. Check
this with `reuse lint`.

### Conventional commits

Use [Conventional Commits](https://www.conventionalcommits.org) for your
commit messages.

```
feat(cli): Add the option -p
```

The CI checks each commit message against `commitlint.yml`. To run the same
check before a push, run `make commitlint`. It checks the commits since
`main` and needs `npm`. Set `COMMIT_BASE` to check against another branch.
To check each message at commit time, run `make hooks` once. It installs a
`commit-msg` hook.

### Sign your work

We use the
[Developer Certificate of Origin (DCO)](https://github.com/embedded-brains/nopinion/blob/main/DCO.txt)
which is included in the repository. Please read this text. If you can
certify it, then add a line like this to every Git commit message of your
contributions:

```
Signed-off-by: Erika Mustermann <erika.mustermann@example.com>
```

Use your real name for contributions to this project.

### Disclose assistance

A commit which a coding assistant helped to write carries an
`Assisted-by:` line immediately before `Signed-off-by:`. Use the form
`AGENT_NAME:MODEL_VERSION [TOOL1] [TOOL2]` of the Linux kernel document
[Documentation/process/coding-assistants.rst](https://docs.kernel.org/process/coding-assistants.html):

```
Assisted-by: Claude:claude-opus-5-5 claude-code
Signed-off-by: Erika Mustermann <erika.mustermann@example.com>
```

Take the model version from the assistant session. Drop a deployment
suffix such as `[1m]`. List only coding assistants and specialised analysis
tools. Git, the compiler and the editor are not tools in this sense.

The person who certifies the DCO signs off. An assistant never signs off
and never appears in a `Co-authored-by:` line.
