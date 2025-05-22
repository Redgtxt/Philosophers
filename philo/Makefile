NAME = philo

SRC_DIR = src
OBJDIR = obj

SRC = $(SRC_DIR)/parsing.c \
	$(SRC_DIR)/philo_init.c \
	$(SRC_DIR)/worker_init.c \
	$(SRC_DIR)/inicialize_program.c \
	$(SRC_DIR)/init_mutexs.c\
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/time.c \
	$(SRC_DIR)/monitor.c\
	$(SRC_DIR)/admin_permissions.c\
	$(SRC_DIR)/eat.c\

OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

CC = cc -g
FLAGS = -Wall -Wextra -Werror

# Colors
GREEN  = \033[0;32m
BLUE   = \033[1;34m
YELLOW = \033[1;33m
RESET  = \033[0m

all: $(NAME)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	@echo "$(BLUE)[Compiling]$(RESET) $<"
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)Build completed successfully.$(RESET)"

clean:
	@echo "$(BLUE)[Cleaning objects]$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(BLUE)[Cleaning everything nicely]$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 