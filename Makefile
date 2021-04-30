# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2021/04/30 15:21:39 by smaccary         ###   ########.fr        #
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
VECT_LIB = C_vectors/vectlib.a
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes -I./C_vectors/includes

SRCS_PATH = src
SRC_LIST =	constants/redirects.c constants/separators.c\
			\
			parsing/parse_parenthesis.c parsing/check_pipeline.c\
			parsing/parser.c parsing/parser_utils.c parsing/tree.c \
			parsing/finders.c parsing/wrapped_finders.c parsing/commands.c \
			parsing/commands_utils.c parsing/wrapped_finders_2.c\
			\
			lexing/multiline.c lexing/split_line.c lexing/tokenizer.c\
			lexing/clear_quotes.c\
			\
			exec/utils.c parsing/checkers.c \
			exec/redirections_utils.c exec/close.c \
			exec/exec_commands.c exec/pipes.c \
			exec/redirections.c exec/exec.c exec/pipeline.c \
			exec/here_doc.c exec/exec_builtins.c\
			\
			garbage_collector/garbage_collector.c garbage_collector/free_ast.c\
			garbage_collector/free_env.c\
			\
			builtins/parenthesis.c builtins/unset.c\
			builtins/pwd.c builtins/builtin_manager.c builtins/export.c\
			builtins/cd.c builtins/echo.c builtins/env.c\
			builtins/exit.c\
			\
			signals/handlers.c signals/singletons.c signals/init_signals.c\
			\
			utils/strjoin_newline.c utils/tab_utils.c utils/list_utils.c \
			\
			termcaps/termcaps.c termcaps/termcaps_utils.c termcaps/cursor.c\
			termcaps/word_jump.c termcaps/get_term_line.c\
			termcaps/hist_utils.c termcaps/history.c termcaps/interactive.c\
			termcaps/copy_paste.c termcaps/history_lines.c termcaps/insert.c\
			termcaps/delete.c termcaps/term_size.c termcaps/move.c\
			termcaps/line_utils.c termcaps/cursor_utils.c termcaps/keys.c\
			\
			expansions/wildcard.c expansions/sub_env.c \
			expansions/remove_quotes.c expansions/perform_expansions.c\
			expansions/expand_command.c\
			\
			env/find_exec.c env/ft_getenv.c env/ft_setenv.c\
			\
			debug/debug_utils.c debug/print_ast.c debug/print_pipeline.c errmgr.c\
			minishell.c  \
			complete_line.c main.c
SRCS =		$(addprefix $(SRCS_PATH), $(SRC_LIST))
OBJS	=	$(addprefix $(OBJ_PATH), $(SRC_LIST:.c=.o))

CPOOP = 

all :		libft
			@mkdir -p ./obj
			$(MAKE) $(NAME)

$(NAME):	$(OBJS) $(VECT_LIB)
			$(CC) $(OBJS) $(LIBS) $(LIBFT_LIB) $(VECT_LIB) -o $(NAME)

libft:
			$(LIBFT_MAKE)

$(VECT_LIB):
	make -C C_vectors

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
