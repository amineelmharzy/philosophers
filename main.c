/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:35:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/24 22:09:46 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_solve	solve;
	int		res;

	if (ac != 5 && ac != 6)
		return (0);
	res = init_solve(&solve, ac, av);
	if (!res)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else if (res == 2)
		return (0);
	run_solve(&solve);
	return (0);
}
