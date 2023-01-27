srcs = $(wildcard *.c)
objs = $(srcs:.c=.o)

main_o = main.o

CC=cc
CFLAGS= -Wall -Wextra 
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : main

main : $(main_o) $(objs)
	$(CC) $(objs) -o philo

clean :
	@rm $(objs)

fclean : clean
	rm philo

re : fclean all
