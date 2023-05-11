/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:31:53 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 21:55:46 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_all_ates(t_solve *solve)
{
	if (solve->nphilos_ates == solve->number_of_philosophers)
	{
		solve->time = get_time(solve);
		solve->nphilos_ates = 0;
	}
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
	solve->nphilos_ates++;
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
			pthread_mutex_lock(&solve->lock);
			philo->is_done = 1;
			pthread_mutex_unlock(&solve->lock);
			return (NULL);
		}
		philosopher(solve, philo);
	}
	return (NULL);
}
