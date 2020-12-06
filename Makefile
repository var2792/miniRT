#cc -I /usr/local/include/ miniRT/start.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CC =			gcc

FLAGS =			-Wall -Wextra -Werror

RM =			rm -rf

DIR_HEADERS =	./includes/

DIR_SRCS =		./srcs/

DIR_OBJS =		./

LIBMLX =		minilibx-linux/libmlx_linux.a minilibx-linux/libmlx.a

SAVE =			-fsanitize=address
6
SRC =			main.c

SRCS =			$(SRC)

COMPIL =		$(FLAGS) $(SAVE)

OBJS =			$(SRCS:.c=.o)

NAME =			miniRT

%.o: %.c
				@gcc $(FLAGS) -I $(DIR_HEADERS) -c $< -o $@
				@echo "Compiled "$<" successfully!"

$(NAME) :		$(OBJS)
				@make -C ./minilibx_mms
				@make -C ./minilibx_opengl
				@cp ./minilibx-linux/libmlx_linux.a libmlx_linux.a
				@cp ./minilibx-linux/libmlx.a libmlx.a
				$(CC) $(COMPIL) -I $(DIR_HEADERS) $(LIBMLX) $(OBJS) -o $(NAME)

all:			$(NAME)

bonus:

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all, clean, fclean, re, bonus
