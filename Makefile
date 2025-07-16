NAME		=	cub3D

CC			=	cc

FLAG		=	-Wall -Werror -Wextra -g3

C_FILE		=	main.c					\
				utils.c					\
				parsing.c				\
				check_file.c			\
				check_access.c			\
				check_texture.c			\
				get_next_line.c			\
				get_next_line_utils.c	\
				check_map.c				\
				check_map_content.c		\

SRC_DIR		=	./src/

SRC			=	$(addprefix $(SRC_DIR), $(C_FILE))

LIBFT_DIR	=	./libft/
LIBFT		=	$(LIBFT_DIR)libft.a

OBJ_PATH	=	$(SRC_DIR)obj/
OBJ			=	$(C_FILE:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

$(OBJ_PATH)%.o: $(SRC_DIR)%.c
				@mkdir -p $(OBJ_PATH)
				$(CC) $(FLAG) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "\033[0;33m\nCOMPILING CUB...\n"
	$(CC) $(FLAG) $(OBJS) $(LIBFT) -I./includes -I$(LIBFT_DIR) -o $(NAME)
	@echo "\033[1;32m./cub3D created\n"

clean:
	@echo "\033[0;31mDeleting cub object files...\n"
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting cub executable...\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
