# SPDX-License-Identifier: BSD-2-Clause

# Copyright (C) 2026 embedded brains GmbH & Co. KG

CC ?= cc

CFLAGS ?= -O2 -g

WARNINGS = -std=c11 -D_DEFAULT_SOURCE -Wall -Wextra -Wshadow -Wconversion

LIB_SOURCES = asi1c.c cli.c decode.c elf.c flow.c powerdown.c report.c \
	tn0009.c tn0011.c tn0012.c tn0013.c tn0016.c tn0018.c

SOURCES = $(LIB_SOURCES) main.c

T_SOURCES = base64-encode.c ioprintf.c iovprintf.c sha256c.c t-test-checks.c \
	t-test-hash-sha256.c t-test-time.c t-test.c testbeginend.c

TEST_SOURCES = $(sort $(wildcard tests/tc-*.c)) tests/ts-nopinion.c \
	tests/tx-support.c tests/tx-wrap.c

TEST_LDFLAGS = -Wl,--wrap=calloc -Wl,--wrap=malloc -Wl,--wrap=fstat \
	-Wl,--wrap=mmap

TEST_CFLAGS = -std=gnu17 -g -D_DEFAULT_SOURCE -Isrc -Itests -Irtems-test/include

SPEC_VENV ?= ../../.venv

CLANG_FORMAT ?= $(SPEC_VENV)/bin/clang-format

BUILD = build

COVERAGE = build-coverage

all: nopinion

nopinion: $(SOURCES:%.c=$(BUILD)/%.o)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)/%.o: src/%.c src/nopinion.h | $(BUILD)
	$(CC) $(CFLAGS) $(WARNINGS) -c -o $@ $<

$(COVERAGE)/nopinion: $(SOURCES:%.c=$(COVERAGE)/%.o)
	$(CC) --coverage -o $@ $^

$(COVERAGE)/%.o: src/%.c src/nopinion.h | $(COVERAGE)
	$(CC) -O0 -g --coverage $(WARNINGS) -c -o $@ $<

$(BUILD) $(COVERAGE):
	mkdir -p $@

%/t/include/dummy/options.h:
	mkdir -p $(dir $@)
	echo '#define RTEMS_BUILD_LABEL "nopinion"' > $@
	echo '#define RTEMS_VERSION_CONTROL_KEY "none"' > \
	  $*/t/include/version-vc-key.h

$(BUILD)/validation: $(LIB_SOURCES:%.c=$(BUILD)/%.o) $(TEST_SOURCES) \
    $(T_SOURCES:%=rtems-test/%) $(wildcard tests/*.h) \
    $(BUILD)/t/include/dummy/options.h
	$(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) -I$(BUILD)/t/include -o $@ \
	  $(LIB_SOURCES:%.c=$(BUILD)/%.o) $(TEST_SOURCES) \
	  $(T_SOURCES:%=rtems-test/%)

$(COVERAGE)/validation: $(LIB_SOURCES:%.c=$(COVERAGE)/%.o) $(TEST_SOURCES) \
    $(T_SOURCES:%=rtems-test/%) $(wildcard tests/*.h) \
    $(COVERAGE)/t/include/dummy/options.h
	$(CC) --coverage $(TEST_CFLAGS) $(TEST_LDFLAGS) \
	  -I$(COVERAGE)/t/include -o $@ \
	  $(LIB_SOURCES:%.c=$(COVERAGE)/%.o) $(TEST_SOURCES) \
	  $(T_SOURCES:%=rtems-test/%)

check: nopinion $(BUILD)/validation
	NOPINION=$(CURDIR)/nopinion $(BUILD)/validation

coverage: $(COVERAGE)/nopinion $(COVERAGE)/validation
	rm -f $(COVERAGE)/*.gcda
	NOPINION=$(CURDIR)/$(COVERAGE)/nopinion $(COVERAGE)/validation
	gcovr --root . --object-directory $(COVERAGE) --filter 'src/[^/]*\.c$$' \
	  --txt-summary --fail-under-line 100 --fail-under-branch 100

generate:
	. $(SPEC_VENV)/bin/activate && specwareexport \
	  --config-file specitems.yml --no-interface-code --format-code \
	  --clang-format-path $(CLANG_FORMAT) \
	  --clang-format-style=file:.clang-format \
	  $$(grep -rl '^test-target: nopinion/tests/' spec/nopinion | sort)

COMMIT_BASE ?= main

COMMITLINT_ARGS ?= --from $(COMMIT_BASE) --to HEAD

COMMITLINT_PREFIX = .commitlint

COMMITLINT_BIN = $(COMMITLINT_PREFIX)/bin/commitlint

commitlint: | $(COMMITLINT_BIN)
	NPM_CONFIG_PREFIX=$(COMMITLINT_PREFIX) $(COMMITLINT_BIN) \
		--config commitlint.yml $(COMMITLINT_ARGS)

# The resolver of commitlint finds the extended configuration in the global
# prefix of npm.
$(COMMITLINT_BIN):
	npm install --silent --global --prefix $(COMMITLINT_PREFIX) \
		@commitlint/cli@19 @commitlint/config-conventional@19
	printf '*\n' >$(COMMITLINT_PREFIX)/.gitignore

COMMIT_MSG_HOOK = $(shell git rev-parse --git-path hooks)/commit-msg

# The hook skips the check on a branch which has no commitlint target.
hooks:
	printf '#!/bin/sh\ngrep -q "^commitlint:" Makefile || exit 0\nexec make -s commitlint COMMITLINT_ARGS="--edit $$1"\n' \
		>$(COMMIT_MSG_HOOK)
	chmod +x $(COMMIT_MSG_HOOK)

clean:
	rm -f nopinion
	rm -rf $(BUILD) $(COVERAGE)

.PHONY: all check clean commitlint coverage generate hooks
