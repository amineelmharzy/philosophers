srcs = actions.c   \
	init.c   \
	run_solve.c   \
	solve.c   \
	utils.c

objs = $(srcs:.c=.o)

philo_src = main.c
philo_obj = main.o
philo = philo

CC=cc
CFLAGS= -Wall -Wextra -Werror

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : philo

$(philo_obj) : $(philo_src)
	$(CC) $(CFLAGS) -c $< -o $@

philo : $(objs) $(philo_obj)
	$(CC) $(philo_obj) $(objs) -o $@

clean :
	rm $(objs)

fclean : clean
	rm $(philo)

bonus : 
	make -C philo_bonus/

re : fclean all
