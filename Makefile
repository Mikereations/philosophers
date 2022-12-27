NAME = philo

SOURCES = ./philo.c ./end.c ./philosophy.c ./start.c ./utils.c

OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
THREADS = -lpthread

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(THREADS)

clean : 
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
