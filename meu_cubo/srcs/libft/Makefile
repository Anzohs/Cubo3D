NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

SRCS = ft_itoa.c ft_strchr.c ft_strjoin.c ft_strlen.c ft_strcpy.c ft_calloc.c \
	ft_bzero.c ft_split.c ft_strdup.c ft_substr.c ft_strncmp.c

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
	@echo "🧹 Libft: objetos limpos!"

fclean: clean
	@rm -f $(NAME)
	@echo "🚮 Libft: biblioteca removida!"

re: fclean all

.PHONY: all clean fclean re
