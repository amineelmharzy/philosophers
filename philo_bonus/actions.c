/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:15:04 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/17 16:52:56 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long	get_time(t_solve *solve)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	(void)solve;
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	think(t_solve *solve, int philo_id)
{
	printf("%llu %d is thinking\n", get_time(solve), philo_id);
}

void	philo_sleep(t_solve *solve, int philo_id)
{
	printf("%llu %d is sleeping\n", get_time(solve), philo_id);
	usleep(solve->time_to_sleep * 1000);
}

void	eat(t_solve *solve, int philo_id)
{
	printf("%llu %d is eating\n", get_time(solve), philo_id);
	usleep(solve->time_to_eat * 1000);
	solve->philosophers[philo_id].is_ates = 1;
	solve->philosophers[philo_id].meals_ates += 1;
}
