
SRCS		= main.c parse_put_scene.c parse_put_canvas.c belong_to_obj.c light_change.c operat_vecs.c parse_file.c parse_file_sec.c check_see_objs.c check_shadows.c points_funs.c belong_points.c errors_file.c

HEADER		= -I parse_put_scene.h parse_put_canvas.h belong_to_obj.h light_change.h operat_vecs.h parse_file.h check_see_objs.h check_shadows.h points_funs.h

OBJS		=	${SRCS:.c=.o}

LIBFT		= libft

CFLAGS		= -Wall -Wextra -Werror

LFLAGS			= -L $(LIBFT) -lft

SNAME := $(shell uname)

ifeq ($(SNAME),Darwin)
	SFLS		= -Lminilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
	SHDRS		= -Imlx
	LIBMLX		= mlx_linux
endif
ifeq ($(SNAME),Linux)
	SFLS		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	SHDRS		= -I/usr/include -Imlx_linux -O3
	LIBMLX		= mlx_linux
endif

CC			= gcc

RM			= rm -rf

NAME		= miniRT

.c.o:		${HEADER}
			${CC} ${CFLAGS} ${SHDRS} -c $< -o $@

${NAME}:	compilelibs ${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LFLAGS} ${SFLS} -o ${NAME}

compilelibs:
			make -s -C $(LIBFT)
			make -s -C $(LIBMLX)

all:		 ${NAME}

clean:
			${RM} ${OBJS} *.gch
			make -s -C $(LIBFT) clean
			@make -s -C $(LIBMLX) clean

fclean:		clean
			${RM} ${NAME}
			make -s -C $(LIBFT) fclean
			@make -s -C $(LIBMLX) clean

re:			fclean all

.PHONY: 	all clean fclean re
