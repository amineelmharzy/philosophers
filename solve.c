/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:31:53 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 19:15:52 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_all_ates(t_solve *solve)
{
	int	i;

	pthread_mutex_lock(&solve->lock);
	i = 0;
	pthread_mutex_unlock(&solve->lock);
	while (i < solve->number_of_philosophers)
	{
		if (!solve->philosophers[i].is_ates)
			return ;
		pthread_mutex_lock(&solve->lock);
		i++;
		pthread_mutex_unlock(&solve->lock);
	}
	pthread_mutex_lock(&solve->lock);
	solve->timestamp = get_time(solve);
	pthread_mutex_unlock(&solve->lock);
}

int	all_ates(t_solve *solve, t_philosopher *philo)
{
	int	meals;

	meals = philo->meals_ates;
	if (solve->number_of_times_each_philosopher_must_eat > 1)
	{
		if (meals == solve->number_of_times_each_philosopher_must_eat)
			return (1);
	}
	return (0);
}

void	philosopher(t_solve *solve, t_philosopher *philo, int *died_philo)
{
	check_all_ates(solve);
	take_forks(solve, philo->philosopher_id);
	if (check_death(philo))
		pthread_mutex_unlock(&solve->writing);
	pthread_mutex_lock(&solve->lock);
	if (solve->is_died == 1)
	{
		pthread_mutex_unlock(&solve->lock);
		pthread_mutex_lock(&solve->lock);
		if (philo->philosopher_id == 0)
			*died_philo = -1;
		else
			*died_philo = philo->philosopher_id;
		philo->time_of_death = get_time(solve);
		pthread_mutex_unlock(&solve->lock);
	}
	pthread_mutex_unlock(&solve->lock);
	eat(solve, philo->philosopher_id);
	puts_forks(solve, philo->philosopher_id);
	think(solve, philo->philosopher_id);
	philo_sleep(solve, philo->philosopher_id);
}

void	*eat_dinner(void *arg)
{
	t_philosopher	*philo;
	t_solve			*solve;
	static int		died_philo;

	philo = arg;
	solve = philo->solve;
	if (philo->philosopher_id % 2 == 1)
		usleep(20);
	while (1)
	{
		if (all_ates(solve, philo))
			return (NULL);
		philosopher(solve, philo, &died_philo);
		pthread_mutex_lock(&solve->lock);
		if (solve->is_died)
		{
			pthread_mutex_unlock(&solve->lock);
			return ((void *) &died_philo);
		}
		pthread_mutex_unlock(&solve->lock);
	}
	return (NULL);
}
