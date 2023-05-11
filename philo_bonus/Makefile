srcs = actions.c   \
	   ft_itoa.c   \
	   init.c   \
	   run_solve.c   \
	   utils.c 

objs = $(srcs:.c=.o)

philo_srcb = main.c
philo_objb = main.o
NAMEB = philo_bonus

CC=cc
CFLAGS= -Wall -Wextra -Werror

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAMEB)

$(philo_objb) : $(philo_srcb)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAMEB) : $(objs) $(philo_objb)
	$(CC) $(philo_objb) $(objs) -o $@

clean :
	rm $(objs) $(philo_objb)

fclean : clean
	rm $(NAMEB)

re : fclean all
