/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:32:29 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 18:17:28 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	launch(t_solve *solve)
{
	int	i;

	check_death(solve);
	i = -1;
	while (++i < solve->number_of_philosophers)
		pthread_detach(solve->philosophers[i].thread_id);
	i = -1;
	while (++i < solve->number_of_philosophers)
		pthread_mutex_destroy(&solve->chopsticks[i]);
	pthread_mutex_destroy(&solve->lock);
	pthread_mutex_destroy(&solve->mut);
}

void	run_solve(t_solve *solve)
{
	int	i;
	int	status;

	i = -1;
	solve->timestamp = get_time(solve);
	solve->time = get_time(solve);
	while (++i < solve->number_of_philosophers)
	{
		solve->philosophers[i].philosopher_id = i;
		solve->philosophers[i].solve = solve;
		solve->philosophers[i].meals_ates = 0;
		solve->philosophers[i].is_ates = 0;
		solve->philosophers[i].is_done = 0;
		solve->philosophers[i].last_ate = get_time(solve);
		status = pthread_create(&solve->philosophers[i].thread_id,
				NULL,
				eat_dinner,
				&solve->philosophers[i]);
		if (status != 0)
			perror("error ");
	}
	launch(solve);
}
