NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror 
RM          = rm -f
HEADER      = libft.h
BUILD_DIR   = build

SRCS        = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c          \
              ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c         \
              ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c       \
              ft_strnstr.c ft_strncmp.c ft_atoi.c                      \
              ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c     \
              ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c       \
              ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c        \
              ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c        \
              ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c            \
              ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c  \
              ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c            \
              ft_lstiter.c gnl.c ft_strcpy.c

OBJS        = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Colours
RESET		= \033[0m
GREEN		= \033[0;92m

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	@echo "$(GREEN)$(NAME) has been made! $(RESET)" 

$(BUILD_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# build dir only deleted when empty. (silently)
clean:
	$(RM) $(OBJS)
	@rmdir $(BUILD_DIR) 2>/dev/null || true

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
