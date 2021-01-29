# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/06 15:35:45 by lothieve          #+#    #+#              #
#    Updated: 2021/01/29 15:28:12 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_strcmp.c ft_atoi.c ft_bzero.c ft_calloc.c ft_free_tab.c ft_indexof.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c ft_isspace.c ft_isupper.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmerge.c ft_lstnew.c ft_lstsize.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memreplace.c ft_memset.c ft_print_memory.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_randstring.c ft_split.c ft_strbegin.c ft_strcat.c ft_strchr.c ft_strcpy.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strncpy.c ft_strndup.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c get_next_line_utils.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c

INCLUDES = includes

OBJS = ${SRCS:.c=.o}

OBJB = ${BONUS:.c=.o}

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

CC = clang

RM = rm -rf

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDES}

bonus:		${OBJS} ${OBJB}
			ar rcs ${NAME} ${OBJS} ${OBJSB}

$(NAME):	${OBJS}
			ar rcs ${NAME} ${OBJS}


clean:		
			${RM} ${OBJS} ${OBJB}

fclean:		clean
			${RM} ${NAME} 

re:			fclean all

.PHONY:		all clean fclean re

