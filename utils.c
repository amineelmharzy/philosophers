/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:33:10 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 19:19:25 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philosopher *philo)
{
	struct timeval		t;
	unsigned long long	ms;

	pthread_mutex_lock(&philo->solve->lock);
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	pthread_mutex_unlock(&philo->solve->lock);
	pthread_mutex_lock(&philo->solve->lock);
	if ((ms - philo->solve->timestamp) > philo->solve->time_to_die)
	{
		pthread_mutex_unlock(&philo->solve->lock);
		pthread_mutex_lock(&philo->solve->lock);
		philo->solve->is_died++;
		pthread_mutex_unlock(&philo->solve->lock);
		pthread_mutex_lock(&philo->solve->writing);
		usleep(100);
		return (1);
	}
	pthread_mutex_unlock(&philo->solve->lock);
	return (0);
}

void	_take_forks(t_solve *solve, int philo_id, int left, int right)
{
	pthread_mutex_unlock(&solve->lock);
	pthread_mutex_lock(&solve->chopsticks[left]);
	pthread_mutex_lock(&solve->chopsticks[right]);
	pthread_mutex_lock(&solve->lock);
	if (!solve->is_died)
		printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
	pthread_mutex_unlock(&solve->lock);
}

void	take_forks(t_solve *solve, int philo_id)
{
	int	right;
	int	left;

	pthread_mutex_lock(&solve->lock);
	right = (philo_id + 1) % solve->number_of_philosophers;
	left = (philo_id + solve->number_of_philosophers)
		% solve->number_of_philosophers;
	pthread_mutex_unlock(&solve->lock);
	pthread_mutex_lock(&solve->lock);
	if (philo_id & 1)
	{
		pthread_mutex_unlock(&solve->lock);
		pthread_mutex_lock(&solve->chopsticks[right]);
		pthread_mutex_lock(&solve->chopsticks[left]);
		pthread_mutex_lock(&solve->lock);
		if (!solve->is_died)
			printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
		pthread_mutex_unlock(&solve->lock);
	}
	else
		_take_forks(solve, philo_id, left, right);
}

void	puts_forks(t_solve *solve, int philo_id)
{
	pthread_mutex_lock(&solve->lock);
	pthread_mutex_unlock(&solve->chopsticks[(philo_id + 1)
		% solve->number_of_philosophers]);
	pthread_mutex_unlock(&solve->chopsticks[(philo_id
			+ solve->number_of_philosophers)
		% solve->number_of_philosophers]);
	pthread_mutex_unlock(&solve->lock);
}
