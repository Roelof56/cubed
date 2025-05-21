NAME		:=	cub3d
CC			:=	clang
LIBMLX		:=	./MLX42
LIBFT		:=	./libft

INCLUDE		:=	-I ./include -I $(LIBMLX)/include
FLAGS		:=	-Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBS		:=	$(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_PATH	:=	src/
OBJ_PATH	:=	objects/

SRC_MI		:=	import_map/file_handling.c \
				import_map/mi_llist_to_array.c \
				import_map/mi_main_import.c \
				import_map/mi_parse_info.c \
				import_map/mi_parse_map.c

SRC_LL		:=	linkedlist/linkedlist.c 

SRCS		:=	main.c \
				draw_minimap.c \
				image.c \
				init.c \
				error.c \
				ft_color.c \
				input_handler.c \
				draw_player_one.c \
				$(SRC_MI) \
				$(SRC_LL)

OBJ			:=	$(SRCS:.c=.o)
OBJS		:=	$(addprefix $(OBJ_PATH), $(OBJ))

# Colours
RESET		= \033[0m
GREEN		= \033[0;92m
RED			= \033[31;01m

# Args for run rule.
ARG0		= maps/map0.cub # Tiny map.
ARG1		= maps/map1.cub # ?
ARG2		= maps/map2.cub # Heeft 2 keer zelfde type identifier.
ARG3		= maps/map3.cub # Mist 1 info line.

# Operations
all				:	createlibs $(NAME)

createlibs		:
					@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
					$(MAKE) -C $(LIBFT)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
					@mkdir -p $(OBJ_PATH)
					@mkdir -p $(OBJ_PATH)/import_map/
					@mkdir -p $(OBJ_PATH)/linkedlist/
					@$(CC) $(FLAGS) -o $@ -c $< $(INCLUDE)

$(NAME)			:	$(OBJS)
					@$(CC) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)
					@echo "$(GREEN)$(NAME) has been made! $(RESET)" 

run				:	all
					./$(NAME) $(ARG0)

run1			:	all
					./$(NAME) $(ARG1)

clean			:
					rm -rf $(OBJ_PATH)
					@rm -rf $(LIBMLX)/build
					$(MAKE) -C $(LIBFT) clean

fclean			:	clean
					@rm -rf $(NAME)
					$(MAKE) -C $(LIBFT) fclean

re				:	clean all

.PHONY			:	all, clean, fclean, re, libmlx, run
