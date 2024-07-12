CC = CC
CFLAGS = -Wall -Wextra -Werror
SRC = main.c mutexes.c utils.c ft_atoi.c
OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)