/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:32:29 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/23 13:32:27 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	launch(t_philosopher philosopher)
{
	t_solve	*solve;

	sem_unlink("/tmp/fork");
	solve = philosopher.solve;
	pthread_create(&philosopher.thread_id, NULL, check_death, &philosopher);
	while (1)
	{
		sem_wait(solve->fork);
		sem_wait(solve->fork);
		eat(solve, philosopher.philosopher_id);
		solve->time = get_time(solve);
		philosopher.meals_ates++;
		sem_post(solve->fork);
		sem_post(solve->fork);
		philo_sleep(solve, philosopher.philosopher_id);
		think(solve, philosopher.philosopher_id);
	}
}

void	run_solve(t_solve *solve)
{
	int	i;

	i = -1;
	gettimeofday(&solve->t, NULL);
	solve->timestamp = (solve->t.tv_sec * 1000) + (solve->t.tv_usec / 1000);
	solve->time = (solve->t.tv_sec * 1000) + (solve->t.tv_usec / 1000);
	while (++i < solve->number_of_philosophers)
	{
		solve->philosophers[i].philosopher_id = i;
		solve->philosophers[i].philosopher_pid = 0;
		solve->philosophers[i].solve = solve;
		solve->philosophers[i].meals_ates = 0;
		solve->philosophers[i].is_ates = 0;
		solve->philosophers[i].is_died = 0;
	}
	i = -1;
	while (++i < solve->number_of_philosophers)
	{
		solve->philosophers[i].philosopher_pid = fork();
		if (solve->philosophers[i].philosopher_pid == 0)
		{
			launch(solve->philosophers[i]);
			exit(0);
		}
	}
}
