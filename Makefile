
SRCS		= main.c gnl/get_next_line.c gnl/get_next_line.h gnl/get_next_line_utils.c parse_put_scene.h parse_put_scene.c file_help_function.c file_help_function.h ft_strlen.c parse_put_canvas.c parse_put_canvas.h belong_to_obj.c belong_to_obj.h light_change.c light_change.h operat_vecs.c operat_vecs.h ft_atoi_float.c parse_file.c parse_file_sec.c parse_file.h

OBJS		=	${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

.c.o:		$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

RM			= rm -rf

NAME		= miniRT

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME}

all:		 ${NAME}

clean:
			${RM} *.o
			clear

fclean:		clean
			${RM} ${NAME} a.out

re:			fclean all

.PHONY: 	all #clean fclean re
