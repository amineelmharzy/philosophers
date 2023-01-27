/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:32:29 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/18 15:18:37 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
void	launch(t_solve *solve)
{
	int	i;
	int	status;

	i = -1;
	while (++i < solve->number_of_philosophers)
	{
		status = pthread_join(solve->philosophers[i].thread_id, NULL);
		if (status != 0)
			perror("error\n");
	}
	i = -1;
	while (++i < solve->number_of_philosophers)
		pthread_mutex_destroy(&solve->chopsticks[i]);
}
*/

void	launch1(t_philosopher philosopher)
{
	t_solve	*solve;

	sem_unlink("/tmp/fork");
	sem_unlink("/tmp/death");
	solve = philosopher.solve;
	pthread_create(&philosopher.thread_id, NULL, check_death, &philosopher);
	/*
	if(philosopher.philosopher_id % 2 == 1)
		usleep(10*1000);
		*/
	while (1)
	{
		sem_wait(solve->fork);
		sem_wait(solve->fork);
		take_forks(solve, philosopher.philosopher_id);
		printf("%llu %d is eating\n", get_time(philosopher.solve), philosopher.philosopher_id);
		usleep(solve->time_to_eat * 1000);
		philosopher.meals_ates++;
		sem_post(solve->fork);
		sem_post(solve->fork);
		solve->timestamp = get_time(solve);
		philo_sleep(solve, philosopher.philosopher_id);
		think(solve, philosopher.philosopher_id);
	}
}

void	*print(void *arg)
{
	(void) arg;
	return (NULL);
}

void	run_solve(t_solve *solve)
{
	int				j;
	int				i;
	struct timeval	time;

	i = -1;
	j = 0;
	//printf("%s\n", solve->semaphore_for_fork);
	gettimeofday(&time, NULL);
	solve->timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (++i < solve->number_of_philosophers)
	{
		solve->philosophers[i].philosopher_id = i;
		solve->philosophers[i].philosopher_pid = 0;
		solve->philosophers[i].solve = solve;
		solve->philosophers[i].meals_ates = 0;
		solve->philosophers[i].is_ates = 0;
		solve->philosophers[i].is_died = 0;
	}
	i = 0;
	while (i < solve->number_of_philosophers)
	{
		solve->philosophers[i].philosopher_pid = fork();
		if (solve->philosophers[i].philosopher_pid == 0)
		{
			launch1(solve->philosophers[i]);
			exit(0);
		}
		i++;
	}
	sem_close(solve->fork);
	sem_unlink(solve->semaphore_for_fork);
}
