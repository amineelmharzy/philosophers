/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:20:51 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 16:29:48 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(t_solve *solve)
{
	int	i;

	i = 0;
	pthread_mutex_init(&solve->writing, NULL);
	pthread_mutex_init(&solve->lock, NULL);
	while (i < solve->number_of_philosophers)
	{
		pthread_mutex_init(&solve->chopsticks[i], NULL);
		i++;
	}
}

void	init_solve(t_solve *solve, int ac, char **av)
{
	solve->number_of_philosophers = atoi(av[1]);
	if (solve->number_of_philosophers == 1)
	{
		printf("%llu %d is died\n", get_time(solve), 0);
		exit(0);
	}
	solve->time_to_die = atoi(av[2]);
	if (atoi(av[2]) <= 0)
		exit(1);
	solve->time_to_eat = atoi(av[3]);
	solve->time_to_sleep = atoi(av[4]);
	solve->is_died = 0;
	if (ac == 6)
		solve->number_of_times_each_philosopher_must_eat = atoi(av[5]);
	else
		solve->number_of_times_each_philosopher_must_eat = 1;
	if (!(solve->number_of_philosophers >= 1 && solve->time_to_eat > 0
			&& solve->time_to_die > 0 && solve->time_to_sleep > 0
			&& solve->number_of_times_each_philosopher_must_eat > 0))
		exit(1);
	solve->status++;
	solve->last_ate = 0;
	init_mutex(solve);
}
