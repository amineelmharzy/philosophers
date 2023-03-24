/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:33:10 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 21:55:55 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_done(t_solve *solve)
{
	int	i;

	i = 0;
	while (i < solve->number_of_philosophers)
	{
		if (!solve->philosophers[i].is_done)
			return (0);
		i++;
	}
	return (1);
}

void	check_death(t_solve *solve)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_unlock(&solve->writing);
		if (check_done(solve))
			return ;
		while (i < solve->number_of_philosophers)
		{
			if (get_time(solve) - solve->time > (unsigned long long)
				solve->time_to_die)
			{
				printf("%lld %d died\n", get_time(solve) - solve->timestamp, i);
				return ;
			}
			i++;
		}
		pthread_mutex_unlock(&solve->writing);
		usleep(200);
	}
}

void	take_forks(t_solve *solve, int philo_id)
{
	pthread_mutex_lock(&solve->chopsticks[(philo_id + 1)
		% solve->number_of_philosophers]);
	pthread_mutex_lock(&solve->chopsticks[(philo_id
			+ solve->number_of_philosophers)
		% solve->number_of_philosophers]);
	printf("%llu %d has taken a fork\n", get_time(solve) - solve->timestamp,
		philo_id);
}

void	puts_forks(t_solve *solve, int philo_id)
{
	pthread_mutex_unlock(&solve->chopsticks[(philo_id + 1)
		% solve->number_of_philosophers]);
	pthread_mutex_unlock(&solve->chopsticks[(philo_id
			+ solve->number_of_philosophers)
		% solve->number_of_philosophers]);
}
