NAME = libftgetnextline.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:%.c=$(SRC_DIR)/%.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "📦 Biblioteca $(NAME) criada com sucesso!"

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "🧹 GetNextLine: objetos limpos!"

fclean: clean
	@rm -f $(NAME)
	@echo "🚮 GetNextLine: biblioteca removida!"

re: fclean all

.PHONY: all clean fclean re
