NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
OFILES = $(CFILES:.c=.o)

CFILES = \
ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memmove.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strrchr.c \
ft_strncmp.c \
ft_memchr.c \
ft_memcmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_itoa.c \
ft_striteri.c \
ft_strmapi.c \
ft_split.c \
ft_strndup.c \
ft_strcmp.c \
ft_free_tab.c \
ft_strjoin_free_s1.c \
ft_strtoll.c


all : $(NAME)
	@echo "--> Created file"

$(NAME) : $(OFILES)
	ar rcs $(NAME) $(OFILES)
	@echo "--> Library archived and indexed"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES)
	@echo "--> Removed object files"

fclean: clean
	rm -f $(NAME)
	@echo "--> Removed $(NAME) file"

re: fclean all
	@echo "--> Recompiled everything"

.PHONY: all clean fclean re
