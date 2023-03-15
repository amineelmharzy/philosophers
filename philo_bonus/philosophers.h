/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:52:30 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 19:27:43 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>

struct	s_solve;

typedef struct s_philosopher
{
	pthread_t		thread_id;
	int				philosopher_id;
	pid_t			philosopher_pid;
	int				meals_ates;
	int				is_ates;
	int				is_died;
	struct s_solve	*solve;
}					t_philosopher;

typedef struct s_solve
{
	struct timeval		t;
	int					number_of_philosophers;
	int					time_to_eat;
	int					time_to_sleep;
	unsigned long long	time_to_die;
	unsigned long long	last_ate;
	int					number_of_times_each_philosopher_must_eat;
	int					all_ates;
	int					is_died;
	int					status;
	int					current_philo;
	unsigned long long	timestamp;
	char				*semaphore_for_fork;
	char				*semaphore_names[255];
	char				*sem_forks[255];
	sem_t				*fork;
	sem_t				*main;
	sem_t				*writing;
	t_philosopher		philosophers[255];
}					t_solve;

void				init_solve(t_solve *solve, int ac, char **av);
void				init_mutex(t_solve *solve);
void				run_solve(t_solve *solve);
void				*philosopher(void *arg);
void				*check_death(void *arg);
unsigned long long	get_time(t_solve *solve);
void				think(t_solve *solve, int philo_id);
void				philo_sleep(t_solve *solve, int philo_id);
void				take_forks(t_solve *solve, int philo_id);
void				eat(t_solve *solve, int philo_id);
void				puts_forks(t_solve *solve, int philo_id);
void				*eat_dinner(void *arg);

#endif
