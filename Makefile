srcs = $(wildcard *.c)
objs = $(srcs:.c=.o)

main_o = main.o

CC=cc
CFLAGS= -Wall -Wextra -Werror
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : main

main : $(main_o) $(objs)
	$(CC) $(objs) -o philo -fsanitize=thread

clean :
	rm $(objs)

fclean : clean
	rm philo

re : fclean all
