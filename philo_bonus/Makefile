srcs = $(wildcard *.c)
objs = $(srcs:.c=.o)

main_o = main.o

CC=cc
CFLAGS= -Wall -Wextra -Werror
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : main

main : $(main_o) $(objs)
	$(CC) $(objs) -o philo_bonus

clean :
	rm $(objs)

fclean : clean
	rm philo_bonus

re : fclean all
