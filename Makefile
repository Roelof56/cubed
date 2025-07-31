NAME		:=	cub3D
CC			:=	cc
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
				parser_file_handling.c \
				parser_main.c \
				parser_load_file.c \
				parser_get_mapinfo.c \
				parser_get_map.c \
				parser_validate_map.c \
				parser_validate_utils.c \
				parser_floodfill.c \
				parser_import_color.c \
				parser_color_utils.c \
				parser_square_map.c \
				parser_textures.c \
				init_mlx.c \
				input.c \
				input_mouse.c \
				draw_utils_bresenham.c \
				draw_utils.c \
				raycaster.c \
				draw_minimap.c \
				dda.c \
				raycaster_utils.c \
				draw_minimap_utils.c


OBJ			:=	$(SRCS:.c=.o)
OBJS		:=	$(addprefix $(OBJ_PATH), $(OBJ))

# Colours
RESET		= \033[0m
GREEN		= \033[0;92m

# Operations
all				:	createlibs $(NAME)

createlibs		:
					cmake $(LIBMLX) -B $(LIBMLX)/build -D CMAKE_C_COMPILER=$(CC) && make -C $(LIBMLX)/build -j4
					$(MAKE) -C $(LIBFT) CC=$(CC)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
					@mkdir -p $(OBJ_PATH)
					@$(CC) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(NAME)			:	$(OBJS)
					@$(CC) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)
					@echo "$(GREEN)$(NAME) has been made! $(RESET)" 

clean			:
					rm -rf $(OBJ_PATH)
					rm -rf $(LIBMLX)/build
					$(MAKE) -C $(LIBFT) clean

fclean			:	clean
					rm -rf $(NAME)
					$(MAKE) -C $(LIBFT) fclean

re				:	clean all

.PHONY			:	all, clean, fclean, re
