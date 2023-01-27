/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:33:10 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/18 15:27:29 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philosopher *philo)
{
	struct timeval		t;
	unsigned long long	ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if ((ms - philo->solve->timestamp) >= philo->solve->time_to_die)
	{
		philo->solve->is_died = 1;
		printf("%llu %d died\n", ms, philo->philosopher_id);
		exit(1);
	}
	return (0);
}

void	take_forks(t_solve *solve, int philo_id)
{
	int	right;
	int	left;

	right = (philo_id + 1) % solve->number_of_philosophers;
	left = (philo_id + solve->number_of_philosophers)
		% solve->number_of_philosophers;
	if (philo_id & 1)
	{
		pthread_mutex_lock(&solve->chopsticks[right]);
		printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
		check_death(&solve->philosophers[philo_id]);
		pthread_mutex_lock(&solve->chopsticks[left]);
		check_death(&solve->philosophers[philo_id]);
		printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
	}
	else
	{
		pthread_mutex_lock(&solve->chopsticks[left]);
		printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
		pthread_mutex_lock(&solve->chopsticks[right]);
		printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
	}
}

void	puts_forks(t_solve *solve, int philo_id)
{
	pthread_mutex_unlock(&solve->chopsticks[(philo_id + 1)
		% solve->number_of_philosophers]);
	pthread_mutex_unlock(&solve->chopsticks[(philo_id
			+ solve->number_of_philosophers)
		% solve->number_of_philosophers]);
}

void	ft_usleep(int ms)
{
	int	i;

	i = 0;
	while (i < ms)
	{
		usleep(1000);
		i++;
	}
}
