CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =	./memory_functions/ft_memset.c ./memory_functions/ft_bzero.c\
		./memory_functions/ft_memcpy.c ./memory_functions/ft_memmove.c\
		./memory_functions/ft_memchr.c ./memory_functions/ft_memcmp.c\
		./memory_functions/ft_calloc.c ./memory_functions/ft_realloc.c\
		./string_functions/ft_isalpha.c ./string_functions/ft_isdigit.c\
		./string_functions/ft_isalnum.c ./string_functions/ft_isascii.c\
		./string_functions/ft_isprint.c\
		./string_functions/ft_strnstr.c\
		./string_functions/ft_strdup.c ./string_functions/ft_substr.c\
		./string_functions/ft_strjoin.c ./string_functions/ft_toupper.c\
		./string_functions/ft_strjoin_three.c\
		./string_functions/ft_tolower.c ./string_functions/ft_strlcpy.c\
		./string_functions/ft_strlen.c  ./string_functions/ft_strlcat.c\
		./string_functions/ft_strchr.c ./string_functions/ft_strrchr.c\
		./string_functions/ft_strtrim.c ./string_functions/ft_strmapi.c\
		./string_functions/ft_strncmp.c ./string_functions/ft_striteri.c\
		./string_functions/ft_putchar_fd.c ./string_functions/ft_putchar.c\
		./string_functions/ft_putstr.c ./string_functions/ft_putstr_fd.c\
		./string_functions/get_next_line.c ./string_functions/ft_putendl_fd.c\
		./string_functions/ft_printf.c ./string_functions/ft_itoa.c\
		./string_functions/ft_strcmp.c ./string_functions/ft_isspace.c\
		./matrix_functions/ft_split.c ./matrix_functions/ft_dup_matrix.c\
		./matrix_functions/ft_free_matrix.c ./matrix_functions/ft_matrix_len.c\
		./int_functions/ft_atoi.c ./int_functions/ft_unsigned_putnbr.c\
		./int_functions/ft_putnbr.c ./int_functions/ft_atol.c\
		./int_functions/ft_putnbr_fd.c ./int_functions/ft_hexadecimal.c\
		./int_functions/ft_forpointer.c\
		./list_functions/ft_lstnew.c ./list_functions/ft_lstadd_front.c\
		./list_functions/ft_lstsize.c ./list_functions/ft_lstlast.c\
		./list_functions/ft_lstadd_back.c ./list_functions/ft_lstdelone.c\
		./list_functions/ft_lstclear.c ./list_functions/ft_lstiter.c\
		./list_functions/ft_lstmap.c\

OBJECTS = ${SRC:.c=.o}

BN_OBJECTS = ${BONUS:.c=.o}

NAME = libft.a

all: $(NAME)

$(NAME):$(OBJECTS)
		@ar rcs $(NAME) $(OBJECTS)

%.o: %.c
		@${CC} -c ${CFLAGS} -I. $< -o $@

clean:
		@rm -rf $(OBJECTS)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
