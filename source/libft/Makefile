# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 16:40:54 by lbrandy           #+#    #+#              #
#    Updated: 2021/01/25 16:10:22 by lbrandy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I. -c

SRC =   ft_memcpy.c ft_memccpy.c ft_strlcat.c ft_memchr.c ft_memmove.c ft_strlcpy.c ft_bzero.c ft_memcmp.c ft_memset.c ft_strlen.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c get_next_line_utils.c

SRC_bonus = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ_bonus = $(SRC_bonus:.c=.o)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus: all $(OBJ_bonus)
	ar rc $(NAME) $(OBJ_bonus)

%.o:%.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re:	fclean all

.PHONY: clean fclean all re bonus

