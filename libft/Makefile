# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarneld <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 14:18:01 by tarneld           #+#    #+#              #
#    Updated: 2020/11/03 14:30:08 by tarneld          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memset.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_memcpy.c ft_memccpy.c ft_bzero.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_puts_fd.c ft_calloc.c ft_strdup.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_atoi_float.c get_next_line.c get_next_line_utils.c

SBNS		=	ft_lstmap.c

OBJS		=	${SRCS:.c=.o}

OBNS		=	${SBNS:.c=.o}

HEADER		= -I libft.h

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

.c.o:		${HEADER}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

RM			= rm -rf

NAME		= libft.a

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		 ${NAME}

bonus:		${OBNS}
			${CC} ${CFLAGS} -c ${SBNS} ${HEADER}
			ar rc ${NAME} ${OBNS}

clean:
			${RM} ${OBJS} ${OBNS} *.gch

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re bonus
