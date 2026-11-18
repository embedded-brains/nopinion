<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

# Security policy

nopinion reads ELF files and archives which may come from an untrusted
source. A crash, a read outside the input or a hang on a malformed input
is a security issue.

## Supported versions

The maintainers fix security issues on the branch `main`.

## Reporting a vulnerability

Report a vulnerability through a
[private security advisory](https://github.com/embedded-brains/nopinion/security/advisories/new)
of GitHub, or by e-mail to specthings@embedded-brains.de. Please do not
open a public issue. Attach the input file which shows the issue, if you
can share it.
