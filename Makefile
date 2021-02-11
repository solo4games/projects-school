# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 15:16:54 by lbrandy           #+#    #+#              #
#    Updated: 2021/02/10 13:52:19 by lbrandy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -Imlx
CC = gcc
LIB = libmlx.dylib
LIBFT_DIR = ./source/libft/
LIBFT = ./source/libft/libft.a
SRCS = cub3D.c parser.c mlx_help.c
OBJDIR = obj/
OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME):$(OBJDIR) $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -Lmlx -lmx -framework OpenGL -framework Appkit $(LIB) $(LIBFT) $(SRCS) -o $(NAME)
$(OBJDIR):
	mkdir $(OBJDIR)
$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# NAME = cub_3d.a
# CFLAGS = -Wall -Wextra -Werror -Imlx
# 
# SRCS = test.c
# OBJDIR = obj/
# OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
# 
# all: $(NAME)
# 
# $(NAME): $(OBJDIR) $(OBJS)
# 	ar rc $(NAME) $(OBJS)
# 	ranlib $(NAME)
# 
#$(OBJDIR):
#	mkdir $(OBJDIR)
# 
# $(OBJDIR)%.o: %.c
# 	gcc $(CFLAGS) -c $< -o $@
# 
# clean:
# 	rm -rf $(OBJDIR)
# 
# fclean: clean
# 	rm -rf $(NAME)
# 
# re: fclean all
# 
# .PHONY: all clean fclean re bonus
