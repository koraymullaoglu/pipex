
NAME = pipex
SRCS = pipex.c pipexct.c 
OBJS = $(SRCS:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)
	

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all


.PHONY: all clean fclean re
