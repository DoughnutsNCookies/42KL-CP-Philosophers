/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:28:12 by schuah            #+#    #+#             */
/*   Updated: 2022/08/16 15:21:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/* Forces the philosopher to die at death time when there is only 1 */
int	force_death(t_philo philo)
{
	usleep(philo.input.death_time * 1000);
	printf("%d\t %d died\n", philo.input.death_time, philo.n);
	return (0);
}

/* Start of the main function */
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
	if (ft_atoi(av[1]) == 1)
		return (force_death(philo[0]));
	return (check_state(philo));
}
