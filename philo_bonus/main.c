/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:35:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/17 16:43:11 by ael-mhar         ###   ########.fr       */
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
	(void) av;
	init_solve(&solve, ac, av);
	run_solve(&solve);
	//printf("%d\n", check_all_ates(&solve));
	//check_d(&solve);
	//while (!check_d(&solve));
	while(waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}
