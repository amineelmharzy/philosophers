srcs = actions.c   \
	   ft_itoa.c   \
	   init.c   \
	   run_solve.c   \
	   utils.c 

objs = $(srcs:.c=.o)

philo_srcb = main.c
philo_objb = main.o
philo_bonus = philo_bonus

CC=cc
CFLAGS= -Wall -Wextra -Werror

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : philo_bonus

$(philo_objb) : $(philo_srcb)
	$(CC) $(CFLAGS) -c $< -o $@

philo_bonus : $(objs) $(philo_objb)
	$(CC) $(philo_objb) $(objs) -o $@

clean :
	rm $(objs)

fclean : clean
	rm $(philo_bonus)

re : fclean all
