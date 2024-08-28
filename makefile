.PHONY: all _mkdirs _tidy clean clean_debug clean_release clean_run

################################## PARAMETERS ##################################

# BUILD_MODE: must be defined, determines symbol table and optimisation level
#   DEBUG: generate debug information, no optimisation
#   RELEASE: strip symbol table, lvl3 optimisation

################################################################################

# compiler flags
#   -Wall: enable most compiler warnings
#   -Wextra: enable extra compiler warnings
#   -std=c++17: use C++17 standard
#   -g: generate debug information
#   -s: strip symbol table
#   -O0: no optimization, more info for debugging
#   -O1: some optimization, reasonable compile time and binary size
#   -O3: most optimization, longest compile time and largest binary size
#   -0s: binary size optimization, smallest binary size

################################################################################


SRC_DIR := src
BUILDS_DIR := builds

NAME := $(shell echo $(BUILD_MODE) | tr '[:upper:]' '[:lower:]')

BUILD_DIR := $(BUILDS_DIR)/$(NAME)
OBJS_DIR := $(BUILD_DIR)/objs

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
EXEC := $(NAME).exe

CXX := g++
CFLAGS := -std=c++17 -Wall -Wextra

ifeq ($(BUILD_MODE), DEBUG)
	CFLAGS += -g -O0
else ifeq ($(BUILD_MODE), RELEASE)
	CFLAGS += -s -O3
else ifeq ($(BUILD_MODE), RUN)
	CFLAGS += -O0
else ifneq ($(BUILD_MODE),)
    $(error BUILD_MODE must be RUN, RELEASE or DEBUG)
endif


all: _mkdirs $(EXEC) _tidy

# target to link objects into executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

# patter rule to compile source file into object file
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

# creates build directory structure
_mkdirs:
	@mkdir -p $(BUILDS_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJS_DIR)

_tidy:
ifeq ($(BUILD_MODE), RELEASE)
	@strip $(EXEC)
	@rm -rf $(OBJS_DIR)
endif

clean:
	@-rm -rf $(BUILDS_DIR)
	@-rm debug.exe
	@-rm release.exe
	@-rm run.exe

clean_debug:
	@-rm -rf $(BUILDS_DIR)/debug

clean_run:
	@-rm -rf $(BUILDS_DIR)/run

clean_release:
	@-rm -rf $(BUILDS_DIR)/release
