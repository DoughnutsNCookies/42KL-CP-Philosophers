/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:28:12 by schuah            #+#    #+#             */
/*   Updated: 2022/08/09 22:09:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* DONE CHECKING */
static int	check_valid(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "Error: Invalid number of input\n", 31));
	while (++i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (write(2, "Error: Input cannot be lesser than 1\n", 37));
		if (str_is_digit(av[i]) == 0)
			return (write(2, "Error: Input must only be numbers\n", 34));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_input	input;
	t_main	main;
	t_fork	fork[MAX];
	t_philo	philo[MAX];

	if (check_valid(ac, av) != 0)
		return (1);
	init_arg(&input, ac, av);
	if (pthread_mutex_init(&main.write_mutex, NULL) != 0)
		return (1);
	main.start_time = get_starttime(NULL);
	if (init_fork(&input, fork) != 0)
		return (1);
	if (init_philo(input, fork, main, philo) != 0)
		return (1);
	return (check_state(philo, input));
}
