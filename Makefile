# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2021/04/09 14:06:11 by lothieve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell
CC		= 	clang
CFLAGS	= 	-Wall -Wextra  -g3  $(INCLUDES)

LIBFT_PATH = ./libft
OBJ_PATH =	./obj/
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft -lncurses 
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes

SRCS_PATH = src
SRC_LIST =	parsing/parser.c parsing/parser_utils.c parsing/tree.c \
			parsing/finders.c parsing/wrapped_finders.c parsing/commands.c \
			parsing/commands_utils.c parsing/fake_constants.c \
			\
			exec/utils.c parsing/checkers.c \
			exec/redirections_utils.c exec/close.c \
			exec/exec_commands.c exec/pipes.c \
			exec/redirections.c exec/exec.c exec/pipeline.c \
			\
			parsing/garbage_collector.c \
			\
			parenthesis.c \
			\
			debug_utils.c word_jump.c errmgr.c find_exec.c \
			tab_utils.c builtin_manager.c export.c cd.c cursor.c echo.c env.c \
			exit.c ft_getenv.c ft_setenv.c get_term_line.c hist_utils.c \
			history.c minishell.c pwd.c termcaps.c \
			termcaps_utils.c tokenizer.c unset.c split_line.c\
			wildcard.c sub_env.c multiline.c remove_quotes.c perform_expansions.c \
			list_utils.c
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
			@mkdir -p `dirname $@`
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


debug:
	$(MAKE) -C  ./libft debug all
	$(MAKE) debug_flags $(NAME)


.PHONY:		all clean fclean re libft debug debug_flags
