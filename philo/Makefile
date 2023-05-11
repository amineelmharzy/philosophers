srcs = actions.c   \
	init.c   \
	run_solve.c   \
	solve.c   \
	utils.c

objs = $(srcs:.c=.o)

philo_src = main.c
philo_obj = main.o
NAME = philo

CC=cc
CFLAGS= -Wall -Wextra -Werror

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(philo_obj) : $(philo_src)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(objs) $(philo_obj)
	$(CC) $(philo_obj) $(objs) -o $@

clean :
	rm $(objs) $(philo_obj)

fclean : clean
	rm $(NAME)

bonus : 
	make -C philo_bonus/

re : fclean all
