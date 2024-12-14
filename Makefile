NAME=so_long
CFLAGS= -Wall -Wextra -Werror
SRCS=main.c get_next_line.c get_next_line_utils.c ft_split.c 

OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	cc -lmlx -framework OpenGL -framework AppKit  $^ -o $@
	
%.o:%.c so_long.h
	cc $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re : fclean all