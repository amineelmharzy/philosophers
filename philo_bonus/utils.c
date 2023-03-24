/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:33:10 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 14:59:04 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_one(t_philosopher *philo)
{
	if ((get_time(philo->solve) - philo->solve->time)
		> (unsigned long long)philo->solve->time_to_die)
	{
		philo->solve->is_died = 1;
		philo->is_died = 1;
		sem_wait(philo->solve->main);
		if (sem_open("main", O_EXCL, 0644, 1) != (sem_t *)-1)
			printf("%llu %d id died\n", get_time(philo->solve)
				- philo->solve->timestamp, philo->philosopher_id);
		sem_post(philo->solve->main);
		sem_unlink("main");
		return (1);
	}
	return (0);
}

int	check_two(t_philosopher *philo)
{
	if (philo->meals_ates
		== philo->solve->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

void	_exit_(char *name, char *sem_name)
{
	unlink(sem_name);
	free(name);
	exit(0);
}

void	*check_death(void *arg)
{
	t_philosopher	*philo;
	char			*name;

	philo = arg;
	name = ft_itoa(philo->philosopher_id);
	unlink(name);
	unlink("/death");
	while (1)
	{
		if (check_one(philo))
			sem_close(sem_open("/death", O_CREAT | O_EXCL, 0644, 1));
		if (sem_open("/death", O_EXCL, 0644, 1) != (sem_t *)-1)
			_exit_(name, "/death");
		if (check_two(philo))
			sem_close(sem_open(name, O_CREAT | O_EXCL, 0664, 1));
		if (sem_open(name, O_EXCL, 0644, 1) != (sem_t *)-1)
			_exit_(name, name);
		usleep(100);
	}
	return (NULL);
}
