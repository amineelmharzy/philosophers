/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:33:10 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 20:18:05 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_one(t_philosopher *philo)
{
	struct timeval		t;
	unsigned long long	ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if ((ms - philo->solve->timestamp) > philo->solve->time_to_die)
	{
		philo->solve->is_died = 1;
		philo->is_died = 1;
		sem_wait(philo->solve->main);
		if (sem_open("main", O_EXCL, 0644, 1) != (sem_t *)-1)
			printf("%llu %d id died\n", ms, philo->philosopher_id);
		sem_post(philo->solve->main);
		sem_unlink("main");
		return (1);
	}
	return (0);
}

static int	len_number(int n)
{
	int		len;
	long	nbr;

	nbr = n;
	if (n == 0)
	{
		return (1);
	}
	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = nbr * (-1);
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		length;
	char	*str;

	nbr = n;
	length = len_number(nbr);
	str = (char *)malloc((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = nbr * (-1);
	}
	str[length--] = '\0';
	while (nbr != 0)
	{
		str[length--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}

int	check_two(t_philosopher *philo)
{
	if (philo->meals_ates
		== philo->solve->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

void	*check_death(void *arg)
{
	t_philosopher	*philo;
	char			*name;

	philo = arg;
	name = ft_itoa(philo->philosopher_id);
	while (1)
	{
		if (check_one(philo))
			sem_close(sem_open("/tmp/death", O_CREAT | O_EXCL, 0644, 1));
		if (sem_open("/tmp/death", O_EXCL, 0644, 1) != (sem_t *)-1)
		{
			sem_unlink("/tmp/death");
			free(name);
			exit(1);
		}
		if (check_two(philo))
			sem_close(sem_open(name, O_CREAT | O_EXCL, 0664, 1));
		if (sem_open(name, O_EXCL, 0644, 1) != (sem_t *)-1)
		{
			sem_unlink(name);
			free(name);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}
