/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:20:51 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 19:25:08 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_solve(t_solve *solve, int ac, char **av)
{
	solve->number_of_philosophers = atoi(av[1]);
	solve->time_to_die = atoi(av[2]);
	solve->time_to_eat = atoi(av[3]);
	solve->time_to_sleep = atoi(av[4]);
	solve->is_died = 0;
	if (ac == 6)
		solve->number_of_times_each_philosopher_must_eat = atoi(av[5]);
	else
		solve->number_of_times_each_philosopher_must_eat = -1;
	if (!(solve->number_of_philosophers > 1 && solve->time_to_eat > 0
			&& solve->time_to_die > 0 && solve->time_to_sleep > 0))
		exit(1);
	solve->last_ate = 0;
	solve->all_ates = 0;
	solve->current_philo = 0;
	solve->fork = sem_open("/tmp/fork", O_CREAT | O_EXCL, 0644,
			solve->number_of_philosophers);
}
