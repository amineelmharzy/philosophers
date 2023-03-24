/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:31:53 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 15:18:52 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_all_ates(t_solve *solve)
{
	int	i;

	pthread_mutex_lock(&solve->lock);
	i = 0;
	while (i < solve->number_of_philosophers)
	{
		if (solve->philosophers[i].is_ates == 0)
		{
			pthread_mutex_unlock(&solve->lock);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&solve->lock);
	pthread_mutex_lock(&solve->lock);
	i = 0;
	while (i < solve->number_of_philosophers)
	{
		solve->philosophers[i].is_ates = 0;
		i++;
	}
	solve->time = get_time(solve);
	pthread_mutex_unlock(&solve->lock);
}

int	all_ates(t_solve *solve, t_philosopher *philo)
{
	int	meals;

	meals = philo->meals_ates;
	if (solve->number_of_times_each_philosopher_must_eat > 0)
	{
		if (meals == solve->number_of_times_each_philosopher_must_eat)
			return (1);
	}
	return (0);
}

void	philosopher(t_solve *solve, t_philosopher *philo)
{
	take_forks(solve, philo->philosopher_id);
	eat(solve, philo->philosopher_id);
	pthread_mutex_lock(&solve->writing);
	check_all_ates(solve);
	pthread_mutex_unlock(&solve->writing);
	puts_forks(solve, philo->philosopher_id);
	philo_sleep(solve, philo->philosopher_id);
}

void	*eat_dinner(void *arg)
{
	t_philosopher	*philo;
	t_solve			*solve;

	philo = arg;
	solve = philo->solve;
	if (philo->philosopher_id % 2 == 1)
		usleep(30);
	while (1)
	{
		if (all_ates(solve, philo))
		{
			philo->is_done = 1;
			return (NULL);
		}
		philosopher(solve, philo);
	}
	return (NULL);
}
