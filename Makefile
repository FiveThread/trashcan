EXE = painimyass


SRC_DIR := src
OBJ_DIR := obj
BIN_DIR_ROOT := bin

EXE := $(BIN_DIR)/$(EXE)
SRC := $(wildcard $(SRC_DIR)/*.c)

CC := gcc
CPPFLAGS = -Iinclude -MMD -MP
CFLAGS   = -Wall -Iinclude
LDFLAGS  = -Llib
LDLIBS   = -lm

ifeq ($(OS),Windows_NT)
	OS = WINDOWS
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME),Linux)
		OS = LINUX
	else
		$(error OS not supported)
	endif
endif

ifeq ($(OS),WINDOWS)
	CFLAGS += -Ithirdparty/include -D_WINDOWS 
	LDFLAGS += -Lthirdparty/lib
	LDLIBS += -lmingw32 -lSDL2main -lSDL2
else ifeq ($(OS),LINUX)
	LDFLAGS += 
	LDLIBS += 
endif

ifeq ($(OS),WINDOWS)
	EXE := $(EXE).exe
endif

BIN_DIR := $(BIN_DIR_ROOT)/$(OS)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

ifeq ($(release),1)
	BIN_DIR := $(BIN_DIR)/release
	CFLAGS += -O3 -DNDEBUG
else
	BIN_DIR := $(BIN_DIR)/debug
	CFLAGS +=  -O0 -g 
endif


.PHONY: all
all: $(BIN_DIR)/$(EXE)

$(BIN_DIR)/$(EXE): $(OBJ)
	@echo "Building executable: $@"
	@mkdir -p $(@D) #
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling: $<"
	@mkdir -p $(@D) #
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@ #

.PHONY: run
run: all
	@echo "Starting program: $(BIN_DIR)/$(EXE)"
	@cd ./$(BIN_DIR); ./$(EXE)
	
.PHONY: clean
clean:
	@echo "Cleaning $(BIN_DIR_ROOT) and $(OBJ_DIR) directories"
	@$(RM) -r $(BIN_DIR_ROOT) #
	@$(RM) -r $(OBJ_DIR) #

.PHONY: debug
debug:
	@echo "Opening $(EXE) in gdb"
	@gdb $(BIN_DIR)\$(EXE)





