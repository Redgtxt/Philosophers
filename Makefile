NAME = philo

SRC_DIR = src
OBJDIR = obj

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/init_threads.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/time.c \


OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

CC = cc -g
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
