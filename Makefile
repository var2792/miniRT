
SRCS		= main.c get_next_line.c get_next_line_utils.c parse_put_scene.c file_help_function.c ft_strlen.c parse_put_canvas.c belong_to_obj.c light_change.c operat_vecs.c ft_atoi_float.c parse_file.c parse_file_sec.c check_see_objs.c check_shadows.c points_funs.c belong_points.c #draw_lines.c drawing_objs.c

OBJS		=	${SRCS:.c=.o}

HEADER		= -I get_next_line.h parse_put_scene.h file_help_function.h parse_put_canvas.h belong_to_obj.h light_change.h operat_vecs.h parse_file.h check_see_objs.h check_shadows.h points_funs.h #draw_lines.h drawing_objs.h


CFLAGS		= -Wall -Wextra
#-Werror

CC			= gcc

RM			= rm -rf

NAME		= miniRT

SNAME := $(shell uname)

ifeq ($(SNAME),Darwin)
	SFLS		= -Lminilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
	SHDRS		= -Imlx
endif
ifeq ($(SNAME),Linux)
	SFLS		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	SHDRS		= -I/usr/include -Imlx_linux -O3
endif

.c.o:		${HEADER}
			${CC} ${CFLAGS} ${SHDRS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${SFLS} -o ${NAME}

all:		 ${NAME}

clean:
			${RM} ${OBJS} *.gch

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re
