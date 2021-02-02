# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2021/02/02 14:59:59 by lothieve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

NAME	=	minishell
CC		= 	clang
CFLAGS	= 	-Wall -Wextra -Werror -DBONUS $(INCLUDES)

LIBFT_PATH = ./libft
OBJ_PATH =	./obj/
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft -lncurses
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes

SRCS_PATH = src
SRC_LIST =	find_exec.c tab_utils.c builtin_manager.c export.c cd.c cursor.c echo.c env.c exit.c ft_getenv.c ft_setenv.c get_term_line.c hist_utils.c history.c methods.c minishell.c parsing.c pwd.c termcaps.c termcaps_utils.c tokenizer.c tokenizer_utils.c unset.c wildcard.c
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
