/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:32:29 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/17 18:26:14 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	run_solve(t_solve *solve)
{
	int				j;
	int				i;
	int				status;
	struct timeval	time;

	i = -1;
	j = 0;
	gettimeofday(&time, NULL);
	solve->timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (++i < solve->number_of_philosophers)
	{
		solve->philosophers[i].philosopher_id = i;
		solve->philosophers[i].solve = solve;
		solve->philosophers[i].meals_ates = 0;
		solve->philosophers[i].is_ates = 0;
		status = pthread_create(&solve->philosophers[i].thread_id,
				NULL,
				eat_dinner,
				&solve->philosophers[i]);
		if (status != 0)
			perror("error\n");
	}
	launch(solve);
}
