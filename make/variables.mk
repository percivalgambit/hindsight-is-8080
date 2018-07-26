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
  -Wunused -Wunused-macros \
  -Wdouble-promotion -Wfloat-equal \
  -Wformat=2  \
  -Wnull-dereference \
  -Wuninitialized -Winit-self -Wundef \
  -Wmissing-include-dirs \
  -Wstrict-overflow=5 \
  -Wwrite-strings \
  -Wswitch-enum \
  -Wconversion \
  -Wshadow -Wredundant-decls \
  -Wmissing-declarations \
  -Wpacked

WARNINGS_CFLAGS := $(COMMON_WARNINGS_FLAGS) \
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

GCC_COMMON_WARNINGS_FLAGS := \
  -Wno-error=suggest-attribute=pure -Wno-error=suggest-attribute=const -Wno-error=suggest-attribute=noreturn -Wno-error=suggest-attribute=format -Wno-error=suggest-attribute=cold -Wno-error=suggest-attribute=malloc \
  -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wsuggest-attribute=cold -Wsuggest-attribute=malloc \
  -Wunused-const-variable=2 \
  -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-signedness \
  -Wshift-overflow=2 \
  -Wstringop-overflow=4 -Wstringop-truncation \
  -Walloc-zero \
  -Warray-bounds=2 \
  -Wcast-align=strict \
  -Wduplicated-cond -Wduplicated-branches -Wlogical-op \
  -Wunsafe-loop-optimizations \
  -Wtrampolines
GCC_WARNINGS_CFLAGS := -Wjump-misses-init
ifeq ($(CC),gcc)
	WARNINGS_CFLAGS += $(GCC_COMMON_WARNINGS_FLAGS) $(GCC_WARNINGS_CFLAGS)
endif
ifeq ($(CXX),g++)
	WARNINGS_CXXFLAGS += $(GCC_COMMON_WARNINGS_FLAGS)
endif
