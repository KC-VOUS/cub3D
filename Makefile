NAME		=	cub3D

CC			=	cc

FLAG		=	-Wall -Werror -Wextra -g3

C_FILE		=	main.c					\
				init.c					\
				utils.c					\
				parsing.c				\
				fill_map.c				\
				mlx_utils.c				\
				check_map.c				\
				raycasting.c			\
				check_file.c			\
				check_color.c			\
				fill_struct.c			\
				fill_player.c			\
				check_access.c			\
				check_texture.c			\
				get_next_line.c			\
				check_map_content.c		\
				get_next_line_utils.c	\
				free_all.c				\

SRC_DIR		=	./src/

SRC			=	$(addprefix $(SRC_DIR), $(C_FILE))

LIBFT_DIR	=	./libft/
LIBFT		=	$(LIBFT_DIR)libft.a

MLX_FILE	=	libmlx.a
MLX_PATH	=	./includes/mlx/
MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))
MLX_FLAG	=	-lX11 -lXext
MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

OBJ_PATH	=	$(SRC_DIR)obj/
OBJ			=	$(C_FILE:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

$(OBJ_PATH)%.o: $(SRC_DIR)%.c
				@mkdir -p $(OBJ_PATH)
				$(CC) $(FLAG) -c $< -o $@

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)  > /dev/null 2>&1

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)  > /dev/null 2>&1

$(NAME): $(OBJS)
	@echo "\033[0;33m\nCOMPILING CUB...\n"
	@$(CC) $(FLAG) $(OBJS) $(LIBFT) $(MLX_EX) -I./includes -I$(LIBFT_DIR) -I$(MLX_PATH) -o $(NAME) -lm
	@echo "\033[1;32m./cub3D created\n"

clean:
	@echo "\033[0;31mDeleting cub object files...\n"
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_DIR) clean  > /dev/null 2>&1
	@$(MAKE) -C $(MLX_PATH) clean  > /dev/null 2>&1
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting cub executable...\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean  > /dev/null 2>&1
	@$(MAKE) -C $(MLX_PATH) clean  > /dev/null 2>&1
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
