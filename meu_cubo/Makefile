NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = srcs

LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

GETNEXTLINE_DIR = $(SRC_DIR)/get_next_line
GETNEXTLINE = $(GETNEXTLINE_DIR)/libftgetnextline.a

OBJ_DIR = objs

SRCS = cub.c validate_args.c cub_clean.c validate_color.c validate_rgb.c cub_utils.c \
	validate_map.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJS) $(LIBFT) $(GETNEXTLINE)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GETNEXTLINE) -o $(NAME)
	@echo "✅ Compilação concluída com sucesso!"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(GETNEXTLINE):
	@$(MAKE) --no-print-directory -C $(GETNEXTLINE_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🛠️ Compilando $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(GETNEXTLINE_DIR) clean
	@echo "🧹 Arquivos objeto removidos!"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C $(GETNEXTLINE_DIR) fclean
	@echo "🚮 Executável removido!"

re: fclean all

.PHONY: all clean fclean re
