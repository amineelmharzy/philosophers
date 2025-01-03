/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:20:51 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 22:56:59 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		is_negative;
	int		i;
	long	number;

	is_negative = 1;
	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative = is_negative * (-1);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * is_negative);
}

void	init_mutex(t_solve *solve)
{
	int	i;

	i = 0;
	while (i < solve->number_of_philosophers)
	{
		pthread_mutex_init(&solve->chopsticks[i], NULL);
		i++;
	}
	pthread_mutex_init(&solve->writing, NULL);
	pthread_mutex_init(&solve->lock, NULL);
	pthread_mutex_init(&solve->mut, NULL);
}

int	init_solve(t_solve *solve, int ac, char **av)
{
	solve->number_of_philosophers = ft_atoi(av[1]);
	if (solve->number_of_philosophers == 1)
	{
		printf("%d %d is died\n", 0, 0);
		return (2);
	}
	solve->time_to_die = ft_atoi(av[2]);
	solve->time_to_eat = ft_atoi(av[3]);
	solve->time_to_sleep = ft_atoi(av[4]);
	solve->is_died = 0;
	solve->nphilos_ates = 0;
	if (ac == 6)
	{
		solve->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (solve->number_of_times_each_philosopher_must_eat <= 0)
			return (0);
	}
	else
		solve->number_of_times_each_philosopher_must_eat = -1;
	if (solve->number_of_philosophers <= 0 || solve->time_to_eat <= 0
		|| solve->time_to_die <= 0 || solve->time_to_sleep <= 0)
		return (0);
	init_mutex(solve);
	return (1);
}
