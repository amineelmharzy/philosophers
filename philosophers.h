/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:52:30 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/17 17:56:24 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_solve;

typedef struct s_philosopher
{
	pthread_t			thread_id;
	int					philosopher_id;
	int					meals_ates;
	int					is_ates;
	struct s_solve		*solve;
}						t_philosopher;

typedef struct s_solve
{
	int					number_of_philosophers;
	int					time_to_eat;
	int					time_to_sleep;
	unsigned long long	time_to_die;
	unsigned long long	last_ate;
	int					number_of_times_each_philosopher_must_eat;
	int					all_ates;
	int					is_died;
	int					status;
	unsigned long long	timestamp;
	pthread_mutex_t		writing;
	pthread_mutex_t		chopsticks[255];
	t_philosopher		philosophers[255];
}						t_solve;

void					init_solve(t_solve *solve, int ac, char **av);
void					init_mutex(t_solve *solve);
void					run_solve(t_solve *solve);
void					*philosopher(void *arg);
int						check_death(t_philosopher *philo);
unsigned long long		get_time(t_solve *solve);
void					think(t_solve *solve, int philo_id);
void					philo_sleep(t_solve *solve, int philo_id);
void					take_forks(t_solve *solve, int philo_id);
void					eat(t_solve *solve, int philo_id);
void					puts_forks(t_solve *solve, int philo_id);
void					*eat_dinner(void *arg);
void					ft_usleep(int ms);

#endif
