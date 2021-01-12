# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2021/01/12 13:08:18 by lothieve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

NAME	=	minishell
CC		= 	clang
CFLAGS	= 	-Wall -Wextra -Werror -g3 $(INCLUDES)

LIBFT_PATH = ./libft
OBJ_PATH =	./obj/
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes

SRCS_PATH = src
SRC_LIST =	minishell.c \
			tokenizer.c \
			wildcard.c \
			methods.c
SRCS =		$(addprefix $(SRCS_PATH), $(SRC_LIST))
OBJS	=	$(addprefix $(OBJ_PATH), $(SRC_LIST:.c=.o))


all :		libft
			@mkdir -p ./obj
			$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBS) $(LIBFT_LIB) -o $(NAME)

libft:
			$(LIBFT_MAKE)

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	$(LIBFT_MAKE) fclean
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)

re : 		fclean all	

.PHONY:		all clean fclean re libft
