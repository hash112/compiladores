# Compiler and flags
CXX := g++
BASE_FLAGS := -std=c++17 -Wall -Wextra -I.
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2
CXXFLAGS ?= $(RELEASE_FLAGS)

# Project structure
SRC_DIR := src
BUILD_DIR := build
TARGET := compiler_analysis

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

ifeq ($(OS),Windows_NT)
EXE_EXT := .exe
RM := del /Q
RMDIR := rmdir /S /Q
MKDIR_BUILD := if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
RUN_CMD := .\$(TARGET)$(EXE_EXT)
else
EXE_EXT :=
RM := rm -f
RMDIR := rm -rf
MKDIR_BUILD := mkdir -p "$(BUILD_DIR)"
RUN_CMD := ./$(TARGET)$(EXE_EXT)
endif

.PHONY: all run clean rebuild

all: $(TARGET)$(EXE_EXT)

$(TARGET)$(EXE_EXT): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILD_DIR):
	@$(MKDIR_BUILD)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(BASE_FLAGS) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS := $(DEBUG_FLAGS)
debug: rebuild

release: CXXFLAGS := $(RELEASE_FLAGS)
release: rebuild

gdb: debug
ifeq ($(OS),Windows_NT)
	gdb .\$(TARGET)$(EXE_EXT)
else
	gdb ./$(TARGET)$(EXE_EXT)
endif

run: all
	$(RUN_CMD)

clean:
	-$(RM) $(TARGET)$(EXE_EXT)
	-$(RMDIR) $(BUILD_DIR)

rebuild: clean all