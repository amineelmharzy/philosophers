/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:33:10 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/18 15:18:02 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_one(t_philosopher *philo)
{
	struct timeval		t;
	unsigned long long	ms;
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if ((ms - philo->solve->timestamp) >= philo->solve->time_to_die)
	{
		philo->solve->is_died = 1;
		philo->is_died = 1;
		printf("%llu %d id died\n", ms, philo->philosopher_id);
		return (1);
	}
	return (0);
}

/*
int	check_two(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->solve->number_of_philosophers)
	{
		if (sem
}
*/

static int      len_number(int n)
{
        int             len;
        long    nbr;

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

char    *ft_itoa(int n)
{
        long    nbr;
        int             length;
        char    *str;

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

size_t  ft_strlen(const char *str)
{
        size_t  len;

        len = 0;
        while (*str != '\0')
        {
                len++;
                str++;
        }
        return (len);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        int             i;
        char    *newstr;
        int             length;

        i = 0;
        if (!s1 || !s2)
                return (NULL);
        length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
        newstr = (char *)malloc(sizeof(char) * (length + 1));
        if (!newstr)
                return (NULL);
        while (*s1)
                newstr[i++] = *s1++;
        while (*s2)
                newstr[i++] = *s2++;
        newstr[i] = '\0';
        return (newstr);
}

int	check_two(t_philosopher *philo)
{
	if (philo->meals_ates == philo->solve->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

char	*sem_name(t_philosopher *philo)
{
	(void) philo;
	char *name = ft_strjoin("ates", ft_itoa(philo->philosopher_id));
	return (name);
}

void *check_death(void *arg)
{
	t_philosopher *philo;
	char	*name;
	
	philo = arg;
	name = sem_name(philo);
	while (1)
	{
		if (check_one(philo))
		{
			sem_close(sem_open("/tmp/death", O_CREAT | O_EXCL , 0644, 1));
		}
		if (sem_open("/tmp/death", O_EXCL , 0644, 1) != (sem_t*)-1)
		{
			sem_unlink("/tmp/death");
			exit(1);
		}
		if (check_two(philo))
		{
			sem_close(sem_open(name, O_CREAT | O_EXCL, 0664, 1));
		}
		if (sem_open(name, O_EXCL, 0644, 1) != (sem_t*) -1)
		{
			sem_unlink(name);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

void	take_forks(t_solve *solve, int philo_id)
{
	printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
	printf("%llu %d has taken a fork\n", get_time(solve), philo_id);
}

/*
void	puts_forks(t_solve *solve, int philo_id)
{
	pthread_mutex_unlock(&solve->chopsticks[(philo_id + 1)
		% solve->number_of_philosophers]);
	pthread_mutex_unlock(&solve->chopsticks[(philo_id
			+ solve->number_of_philosophers)
		% solve->number_of_philosophers]);
	printf("%llu\tPhilosopher %d finished his meal 🤮\n", get_time(solve),
		philo_id);
}
*/
