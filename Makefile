# Makefile para compilar y ejecutar el juego usando CMake.

SFML_DIR ?= $(CURDIR)/SFML-2.6.1/lib/cmake/SFML
BUILD_DIR ?= build
CONFIG    ?= Debug

ifeq ($(OS),Windows_NT)
    EXE_SUFFIX := .exe
    RUN_CMD    := cmd /c
else
    EXE_SUFFIX :=
    RUN_CMD    :=
endif

TARGET := $(BUILD_DIR)/bin/amor.depende.de.ti$(EXE_SUFFIX)

.PHONY: all build run clean

all: build

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(CONFIG) -DSFML_DIR="$(SFML_DIR)"
	cmake --build $(BUILD_DIR) --config $(CONFIG)

run: build
	cd "$(CURDIR)" && "$(CURDIR)/$(TARGET)"

clean:
	rm -rf $(BUILD_DIR)
