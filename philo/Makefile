NAME = philo

CC = cc
C_FLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

SRCS_DIR = srcs
SRCS =  $(SRCS_DIR)/check_args.c $(SRCS_DIR)/init_table.c \
	$(SRCS_DIR)/routine.c $(SRCS_DIR)/time.c $(SRCS_DIR)/philosophers.c
OBJ_DIR = objets
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

HEADER = -I./includes

GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
ORANGE = \033[38;5;214m
PURPLE = \033[1;35m
BOLD := \033[1m
RESET = \033[0m

SUCCESS = [ ✔ ]
ERROR = [ ✗ ]
CLEAN = [ ♻ ]
REMOVE = [ 🗑 ]
REDO = [ 🗘 ]

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(C_FLAGS) $(OBJS) $(HEADER)  -o $(NAME) || (echo "\n$(RED) ============ $(ERROR) Linking failed ! ====================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Executable created ! ================================== $(RESET)"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(C_FLAGS) -c $< -o $@ $(HEADER) || (echo "\n$(RED) ============ $(ERROR) Compilation failed ! ================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Successful compilation ! ============================== $(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW) ============ $(CLEAN) Successful binary & dependances cleaning ! ============ $(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BOLD)$(ORANGE) ============ $(REMOVE) Deleted executable ! ================================== $(RESET)"

re: fclean all
	@echo "$(PURPLE) ============ $(REDO) Redo completed ! ====================================== $(RESET)"

.PHONY: all clean fclean re
