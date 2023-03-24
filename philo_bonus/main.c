/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:35:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 16:59:09 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_solve	solve;

	if (ac != 5 && ac != 6)
		return (0);
	if (!init_solve(&solve, ac, av))
		return (0);
	sem_unlink("main");
	sem_unlink("writing");
	sem_unlink("/tmp/fork");
	sem_unlink("/death");
	solve.main = sem_open("main", O_CREAT | O_EXCL, 0644, 1);
	solve.writing = sem_open("writing", O_CREAT | O_EXCL, 0644, 1);
	run_solve(&solve);
	while (waitpid(-1, NULL, 0) > 0)
		;
	sem_close(solve.fork);
	sem_unlink("main");
	sem_unlink("writing");
	sem_unlink("/tmp/fork");
	return (0);
}
