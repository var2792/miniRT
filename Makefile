
SRCS		= srcs/main.c srcs/key_press.c srcs/print_pic.c srcs/fatal_error_mes.c srcs/parse_file.c srcs/parse_file_1utils.c srcs/parse_file_2utils.c srcs/utils.c srcs/operat_vecs.c srcs/coord_on_canvas.c srcs/points_funs.c srcs/objs_selection.c srcs/sphere.c srcs/objs_utils.c srcs/plane.c srcs/square.c srcs/triangle.c srcs/cylinder.c srcs/cylinder_utils.c srcs/cylinder_heads.c  srcs/save_pic.c
HEADER		= -I incs/type_def.h incs/funct_def.h

OBJS		=	${SRCS:.c=.o}

LIBFT		= libft

CFLAGS		= -Wall -Wextra #-Werror

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
			@make -s -C $(LIBFT)
			@make -s -C $(LIBMLX)

all:		 ${NAME}

clean:
			${RM} ${OBJS} *.gch
			@make -s -C $(LIBFT) clean
			@make -s -C $(LIBMLX) clean

fclean:		clean
			${RM} ${NAME}
			@make -s -C $(LIBFT) fclean
			@make -s -C $(LIBMLX) clean

re:			fclean all

.PHONY: 	all clean fclean re
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./miniRT tests/work.rt
