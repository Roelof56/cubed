NAME		:=	cub3d
CC			:=	clang
LIBMLX		:=	./MLX42
LIBFT		:=	./libft

INCLUDE		:=	-I ./include -I $(LIBMLX)/include
FLAGS		:=	-Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBS		:=	$(LIBFT)/libft.a  $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_PATH	:=	src/
OBJ_PATH	:=	objects/

SRCS		:=	main.c \
				new_linkedlist.c \
				parser_error.c \
				parser_main.c \
				parser_load_file.c \
				parser_get_mapinfo.c \
				parser_get_map.c \
				parser_validate_map.c \
				parser_validate_utils.c \
				parser_floodfill.c \
				parser_printer.c \
				init_mlx.c \
				key_input_handler.c \
				draw_minimap.c \
				draw_minimap_player.c \
				draw_utils_color.c \
				draw_fov.c \
				draw_mm.c

OBJ			:=	$(SRCS:.c=.o)
OBJS		:=	$(addprefix $(OBJ_PATH), $(OBJ))

# Colours
RESET		= \033[0m
GREEN		= \033[0;92m
RED			= \033[31;01m

# Args for run rule.
ARG0		= map0.cub # Tiny map.

# Operations
all				:	createlibs $(NAME)

createlibs		:
					cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
					$(MAKE) -C $(LIBFT)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
					@mkdir -p $(OBJ_PATH)
					@$(CC) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(NAME)			:	$(OBJS)
					@$(CC) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)
					@echo "$(GREEN)$(NAME) has been made! $(RESET)" 

run				:	all
					./$(NAME) $(ARG0)

clean			:
					rm -rf $(OBJ_PATH)
					rm -rf $(LIBMLX)/build
					$(MAKE) -C $(LIBFT) clean

fclean			:	clean
					rm -rf $(NAME)
					$(MAKE) -C $(LIBFT) fclean

re				:	clean all

.PHONY			:	all, clean, fclean, re, run
