CC = gcc -fsanitize=thread -g3
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = philo.c check_args.c utils.c threads.c 
OBJ = $(SRC:%c=%o)
NAME = philo

all : $(NAME)
	
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all