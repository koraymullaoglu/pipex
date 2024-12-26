NAME	=	pipex

SRCS	=	pipex.c pipexct.c libft/libft.a

CC	=	gcc
RM	=	rm -f
FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make all -C libft
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
		make clean -C libft
		$(RM) $(NAME)

fclean: clean
		make fclean -C libft
		
re: fclean all

.PHONY: all clean fclean re