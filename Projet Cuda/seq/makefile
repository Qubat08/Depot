# MAIN CONFIGURATION
EXEC = main
PROJECT_NAME = projet

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

# SUFFIXES
.SUFFIXES: .c .o

# OBJECTS
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
EXEC_O = $(BIN_DIR)/$(EXEC)

# COMPILER FLAGS
CC = gcc
CCFLAGS_STD =
CCFLAGS_DEBUG = -D _DEBUG_ 
CCFLAGS = $(CCFLAGS_STD) -I$(INCLUDE_DIR)
CCLIBS = -lm -O2 -Wno-unused-result

# RULES
all: msg $(EXEC_O)
	@mv $(BIN_DIR)/$(EXEC) .

msg:
	@echo "Creating objects and directories..."
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -c $< -o $@ $(CCLIBS)

$(EXEC_O): $(OBJ)
	@echo "Creating executable..."
	@$(CC) -o $@ $^ $(CCLIBS)
	@echo "Done."

debug: CCFLAGS = $(CCFLAGS_STD) $(CCFLAGS_DEBUG)
debug: all

clean:
	@echo "Deleting objects, temporary files..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(EXEC)
	@echo "Done."

depend:
	@echo "Creating dependencies..."
	@sed -e "/^# DEPENDENCIES/,$$ d" Makefile > dependencies
	@echo "# DEPENDENCIES" >> dependencies
	@$(CC) -MM $(SRC) $(CCFLAGS) >> dependencies
	@cat dependencies > Makefile
	@rm dependencies
	@echo "Done."

.PHONY: all msg debug clean depend
