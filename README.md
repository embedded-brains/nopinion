<!--
SPDX-License-Identifier: CC-BY-SA-4.0

Copyright (C) 2026 embedded brains GmbH & Co. KG
-->

# nopinion

nopinion checks the machine code of SPARC ELF files for the instruction
sequences of hardware errata of the Gaisler LEON3FT and LEON4 processors.
Each finding is its opinion on a missing NOP. A finding is *definite* when
the instructions decide it. It is *possible* when it needs an instruction
which the file does not fix.

The checks follow the errata documents and technical notes of the vendor
and the SPARC Architecture Manual Version 8.

| Option `-t` | Erratum |
| --- | --- |
| `0009` | GRLIB-TN-0009, stale cache entry after a store with a data tag parity error |
| `0011` | GRLIB-TN-0011, AHB lock release during an atomic operation |
| `0012` | GRLIB-TN-0012, incorrect annulation of a floating-point operation |
| `0013` | GRLIB-TN-0013, missing FDIV or FSQRT result |
| `0016` | GRLIB-TN-0016, FSR behaviour of the GRFPC |
| `0018` | GRLIB-TN-0018, RETT restart |
| `gr712rc-8` | GR712RC erratum 8, bus access after power-down |
| `gr712rc-19`, `gr740-20-1` | stores with the address space identifier 0x1C |

The option `-p` selects the errata of one part: `gr712rc`, `gr740`,
`leon3ft-rtax`, `ut699`, `ut699e` or `ut700`.

The option `-f sarif` writes the report as a log of the Static Analysis
Results Interchange Format (SARIF) Version 2.1.0. With the option
`-b NAME=DIR`, the log gives the URI of each file below the directory `DIR`
relative to the URI base id `NAME`. The option may repeat, and the longest
directory which contains a file applies. The log does not hold the absolute
paths of the directories, so a reader of the log resolves each `NAME`. A
member of an archive is a nested artifact of its archive.

## Build

nopinion is one C program without dependencies beyond a C11 compiler and
the C library of a POSIX system.

```sh
make
./nopinion -p gr712rc libfoo.a
```

`./nopinion -h` prints the options and the exit status.

## Test

```sh
make check
make coverage
```

The requirements below `spec/nopinion/` generate the tests in `tests/`.
`make coverage` needs `gcovr` and fails below 100% line coverage and 100%
branch coverage.

## Contributing

Please read the [contributing guidelines](CONTRIBUTING.md) and the
[code of conduct](CODE_OF_CONDUCT.md). Report a security issue as
[SECURITY.md](SECURITY.md) describes.

## License

The code is under the BSD-2-Clause license, see [LICENSE.md](LICENSE.md).
The specification items and the documentation are under CC-BY-SA-4.0 or
BSD-2-Clause. Each file names its license in an SPDX line or in
`REUSE.toml`.
