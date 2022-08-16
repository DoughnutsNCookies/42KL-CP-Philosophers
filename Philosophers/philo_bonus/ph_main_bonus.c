/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:35:22 by schuah            #+#    #+#             */
/*   Updated: 2022/08/16 13:56:08 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Returns 0 if the input is valid, else returns a positive number */
static int	check_valid(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "Error: Invalid number of input\n", 31));
	while (++i < ac)
	{
		if (str_is_digit(av[i]) == 0)
			return (write(2, "Error: Input must only be numbers\n", 34));
		if (ft_atoi(av[i]) <= 0)
			return (write(2, "Error: Input number must be bigger than 1\n", 42));
	}
	return (0);
}

/* Start of the main function */
int	main(int ac, char **av)
{
	t_input	input;
	t_philo	philo;

	if (check_valid(ac, av) != 0)
		return (1);
	init_arg(&input, ac, av);
	philo.pid = malloc(sizeof(pid_t) * input.n_philo);
	if (philo.pid == NULL)
		return (1);
	if (init_philo(&philo, input) == 1)
	{
		free(philo.pid);
		return (1);
	}
	return (0);
}
