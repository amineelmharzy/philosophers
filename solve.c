/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:31:53 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/18 15:26:12 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_ates(t_solve *solve)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < solve->number_of_philosophers)
	{
		if (solve->philosophers[i].is_ates == 1)
			count++;
		i++;
	}
	return (count);
}

int	check_all_ates(t_solve *solve)
{
	int	i;

	i = 0;
	while (i < solve->number_of_philosophers)
	{
		if (!solve->philosophers[i].is_ates)
			return (0);
		i++;
	}
	return (1);
}

void	must_eat(t_solve *solve, t_philosopher *philo)
{
	int	id;

	id = philo->meals_ates;
	if (solve->number_of_times_each_philosopher_must_eat > 1)
	{
		if (id == solve->number_of_times_each_philosopher_must_eat)
			exit(0);
	}
}

void	*philosopher(void *arg)
{
	t_philosopher	*philo;
	t_solve			*solve;

	philo = arg;
	solve = philo->solve;
	must_eat(solve, philo);
	take_forks(solve, philo->philosopher_id);
	solve->last_ate = get_time(solve);
	eat(solve, philo->philosopher_id);
	check_death(philo);
	puts_forks(solve, philo->philosopher_id);
	philo_sleep(solve, philo->philosopher_id);
	think(solve, philo->philosopher_id);
	return (NULL);
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
		if (check_all_ates(solve))
		{
			solve->timestamp = get_time(solve);
		}
		philosopher(arg);
		philo_sleep(solve, philo->philosopher_id);
		think(solve, philo->philosopher_id);
	}
	return (NULL);
}
