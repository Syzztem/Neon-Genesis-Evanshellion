# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2021/03/01 16:14:31 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell
CC		= 	clang
CFLAGS	= 	-Wall -Wextra -g3 -DBONUS $(INCLUDES)

LIBFT_PATH = ./libft
OBJ_PATH =	./obj/
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft -lncurses
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes

SRCS_PATH = src
SRC_LIST =	parser.c parser_utils.c parsing.c exec.c debug_utils.c word_jump.c errmgr.c find_exec.c tab_utils.c builtin_manager.c export.c cd.c cursor.c echo.c env.c exit.c ft_getenv.c ft_setenv.c get_term_line.c hist_utils.c history.c methods.c minishell.c parsing.c pwd.c termcaps.c termcaps_utils.c tokenizer.c tokenizer_utils.c unset.c wildcard.c
SRCS =		$(addprefix $(SRCS_PATH), $(SRC_LIST))
OBJS	=	$(addprefix $(OBJ_PATH), $(SRC_LIST:.c=.o))

CPOOP = 

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

debug_flags : 
	$(eval CFLAGS += -D DEBUG=1  -fsanitize=address)
	$(eval LIBFT_LIB += -fsanitize=address)
	@mkdir -p ./obj


debug : fclean
	$(MAKE) -C  ./libft debug re
	$(MAKE) debug_flags $(NAME)

.PHONY:		all clean fclean re libft debug debug_flags
