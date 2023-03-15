/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:35:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 19:44:32 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_d(t_solve *solve)
{
	int	i;

	i = 0;
	while (i < solve->number_of_philosophers)
	{
		if (solve->philosophers[i].is_died == 1)
			return (1);
		printf("%d\n", solve->philosophers[i].is_ates);
		printf("%d\n", solve->philosophers[i].is_died);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_solve	solve;

	if (ac != 5 && ac != 6)
		return (0);
	(void)av;
	init_solve(&solve, ac, av);
	sem_unlink("main");
	sem_unlink("writing");
	solve.main = sem_open("main", O_CREAT | O_EXCL, 0644, 1);
	solve.writing = sem_open("writing", O_CREAT | O_EXCL, 0644, 1);
	run_solve(&solve);
	while (waitpid(-1, NULL, 0) > 0)
		;
	sem_close(solve.fork);
	sem_unlink("/tmp/fork");
	sem_unlink("main");
	sem_unlink("writing");
	return (0);
}
