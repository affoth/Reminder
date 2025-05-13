
NAME = Reminder_exe

SRC_DIR = src/
SRC = reminder.c
SRC := $(addprefix $(SRC_DIR), $(SRC))

OBJDIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJDIR)/%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I/usr/include -Ilibs/minilibx-linux
LDFLAGS = -Llibs/minilibx-linux
LDLIBS = -lmlx
LFLAGS = -lbsd -lXext -lX11 -lm

RM = rm -rf

LIBMLX = libs/minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(LIBMLX):
	@echo "Checking for MiniLibX..."
	@test -d libs/minilibx-linux || (echo "Cloning MiniLibX..." && git clone --quiet https://github.com/42Paris/minilibx-linux.git libs/minilibx-linux)
	@echo "Building MiniLibX..."
	@$(MAKE) -s -C libs/minilibx-linux > /dev/null
	@echo "MiniLibX ready."

$(OBJDIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBMLX) $(OBJ)
	@echo "Linking executable: $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS)
	@echo "Build complete."

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) libs/minilibx-linux
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
