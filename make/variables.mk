SHELL := /bin/bash
CXX := g++
CC := gcc
COMMON_FLAGS := -pedantic -Wall -Wextra -march=native -pipe -MMD -MP -Isrc/
CXXFLAGS := -std=c++17 $(COMMON_FLAGS) -fdiagnostics-show-template-tree -fno-exceptions -fno-rtti
CFLAGS := -std=c17 $(COMMON_FLAGS)

RELEASE_CFLAGS := -O3 -flto
RELEASE_CXXFLAGS := $(RELEASE_CFLAGS)
RELEASE_LDFLAGS := -flto

DEBUG_CFLAGS := -Og -ggdb3 -Werror
DEBUG_CXXFLAGS := $(DEBUG_CFLAGS)

ASSERTS_CPPFLAGS := -DDEBUG
NOASSERTS_CPPFLAGS := -DNDEBUG

COMMON_WARNINGS_FLAGS := \
  -Wno-error=suggest-attribute=pure -Wno-error=suggest-attribute=const -Wno-error=suggest-attribute=noreturn -Wno-error=suggest-attribute=format -Wno-error=suggest-attribute=cold -Wno-error=suggest-attribute=malloc \
  -Wunused -Wunused-const-variable=2 -Wunused-macros \
  -Wdouble-promotion -Wfloat-equal \
  -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-signedness \
  -Wnull-dereference \
  -Wuninitialized -Winit-self -Wundef \
  -Wmissing-include-dirs \
  -Wshift-overflow=2 -Wstrict-overflow=5 \
  -Wstringop-overflow=4 -Wstringop-truncation -Wwrite-strings \
  -Wswitch-enum \
  -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wsuggest-attribute=cold -Wsuggest-attribute=malloc \
  -Walloc-zero \
  -Warray-bounds=2 \
  -Wcast-align=strict -Wconversion \
  -Wshadow -Wredundant-decls -Wduplicated-cond -Wduplicated-branches -Wlogical-op \
  -Wunsafe-loop-optimizations \
  -Wmissing-declarations \
  -Wpacked \
  -Wtrampolines
WARNINGS_CFLAGS := $(COMMON_WARNINGS_FLAGS) \
  -Wjump-misses-init \
  -Wbad-function-cast \
  -Wstrict-prototypes -Wmissing-prototypes \
  -Wold-style-definition \
  -Wnested-externs
WARNINGS_CXXFLAGS := $(COMMON_WARNINGS_FLAGS) \
  -Wold-style-cast -Wuseless-cast \
  -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override \
  -Wplacement-new=2 \
  -Wzero-as-null-pointer-constant \
  -Wextra-semi
