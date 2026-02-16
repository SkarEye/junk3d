#           _____                     _____                     _____                     _____                     _____          
#          /\    \                   /\    \                   /\    \                   /\    \                   /\    \         
#         /::\    \                 /::\____\                 /::\    \                 /::\    \                 /::\    \        
#        /::::\    \               /:::/    /                /::::\    \                \:::\    \               /::::\    \       
#       /::::::\    \             /:::/    /                /::::::\    \                \:::\    \             /::::::\    \      
#      /:::/\:::\    \           /:::/    /                /:::/\:::\    \             ___\:::\    \           /:::/\:::\    \     
#     /:::/  \:::\    \         /:::/    /                /:::/__\:::\    \           /\   \:::\    \         /:::/  \:::\    \    
#    /:::/    \:::\    \       /:::/    /                /::::\   \:::\    \         /::\   \:::\    \       /:::/    \:::\    \   
#   /:::/    / \:::\    \     /:::/    /      _____     /::::::\   \:::\    \     ___\:::\   \:::\    \     /:::/    / \:::\    \  
#  /:::/    /   \:::\    \   /:::/____/      /\    \   /:::/\:::\   \:::\ ___\   /\   \:::\   \:::\    \   /:::/    /   \:::\ ___\ 
# /:::/____/     \:::\____\ |:::|    /      /::\____\ /:::/__\:::\   \:::|    | /::\   \:::\   \:::\____\ /:::/____/     \:::|    |
# \:::\    \      \::/    / |:::|____\     /:::/    / \:::\   \:::\  /:::|____| \:::\   \:::\  /:::/    / \:::\    \     /:::|____|
#  \:::\    \      \/____/   \:::\    \   /:::/    /   \:::\   \:::\/:::/    /   \:::\   \:::\/:::/    /   \:::\    \   /:::/    / 
#   \:::\    \                \:::\    \ /:::/    /     \:::\   \::::::/    /     \:::\   \::::::/    /     \:::\    \ /:::/    /  
#    \:::\    \                \:::\    /:::/    /       \:::\   \::::/    /       \:::\   \::::/    /       \:::\    /:::/    /   
#     \:::\    \                \:::\__/:::/    /         \:::\  /:::/    /         \:::\  /:::/    /         \:::\  /:::/    /    
#      \:::\    \                \::::::::/    /           \:::\/:::/    /           \:::\/:::/    /           \:::\/:::/    /     
#       \:::\    \                \::::::/    /             \::::::/    /             \::::::/    /             \::::::/    /      
#        \:::\____\                \::::/    /               \::::/    /               \::::/    /               \::::/    /       
#         \::/    /                 \::/    /                 \__/____/                 \::/    /                 \__/____/        
#          \/____/                   \/____/                                             \/____/                                 
# === Project name ===
NAME		= cub3d

# === Compiler and Flags ===
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
EXPLICIT 	?= 0

# === Directories ===
UTILS_DIR	= utils
SRC_DIR		= src
INC_DIR		= include
OBJ_DIR		= .obj

# === Mandatory Source files ===
SRC			= 
# === Object files ===
OBJ			= $(addprefix $(OBJ_DIR)/$(SRC:.c=.o))
DEP			= $(OBJ:.o=.d)


# === Escape codes ===
RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
RED			= \033[31m
PURPLE		= \033[35m
GRAY		= \033[90m
UP			= \033[A
CLEAR		= \033[2K

# === Build rules ===
BUILD		?= Default
DEBUG_MSG	:=

ifeq ($(BUILD), debug)
CFLAGS		+= -DDEBUG=1
EXPLICIT	:= 1
DEBUG_MSG	:= @echo "$(PURPLE)DEBUG mode is activated.$(RESET)"
else ifneq ($(BUILD), Default)
$(error Unknown BUILD option: '$(BUILD)'. Valid options are: c98, debug, Default)
endif

# === Default target ===
all: $(NAME)

# === Compilation rules ===
# - Executable -
$(NAME): $(OBJ)
	@echo "$(BLUE)Linking [$(NAME)]...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)$(NAME) compiled successfully.$(RESET)"
	$(DEBUG_MSG)


# - Objects -
$(OBJ_DIR)/$(OBJ_SUBDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@echo "$(GRAY)$(CC) $(CFLAGS) $(INC_FLAGS) -MMD -c $< -o $@$(RESET)"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -MMD -c $< -o $@
	@if [ "$(EXPLICIT)" = "0" ]; then \
		printf "$(UP)$(CLEAR)$(UP)$(CLEAR)"; \
	fi

# === Cleaning rules ===
# - clean -
clean:
	@if [ -d $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(RED)Removing object files...$(RESET)"; \
	else \
		echo "$(YELLOW)No object files to remove.$(RESET)"; \
	fi

# - fclean -
fclean: clean
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME); \
		echo "$(RED)Removing executable $(NAME)...$(RESET)"; \
	else \
		echo "$(YELLOW)No executable $(NAME) to remove.$(RESET)"; \


# - re -
re: fclean all

# === Dependencies ===
-include $(DEP)

# === Help ===
help:
	@echo "Makefile for $(NAME)\n"
	@echo "Available targets:"
	@echo "  all     - Compile the project (default)"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove object files and executable"
	@echo "  re      - Recompile the project"
	@echo "  help    - Display this help message\n"
	@echo "Build options:"
	@echo "  BUILD=debug  - compile with debug information\n"
	@echo "Set EXPLICIT=1 to show detailed compilation output."

.PHONY: all clean fclean re help