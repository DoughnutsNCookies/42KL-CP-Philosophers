/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:18:08 by schuah            #+#    #+#             */
/*   Updated: 2022/08/15 15:53:32 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initializes the variables into the struct based on the user input */
void	init_arg(t_input *input, int ac, char **av)
{
	input->n_philo = ft_atoi(av[1]);
	input->death_time = ft_atoi(av[2]);
	input->eat_time = ft_atoi(av[3]);
	input->sleep_time = ft_atoi(av[4]);
	input->eat_req = 0;
	input->eat_max = 0;
	if (ac == 6)
	{
		input->eat_max = ft_atoi(av[5]);
		input->eat_req = 1;
	}
}

/* Initializes the fork mutexs for each number of philosophers */
int	init_fork(t_input *input, t_fork *fork)
{
	int	i;

	i = -1;
	while (++i < input->n_philo)
	{
		if (pthread_mutex_init(&fork[i].fork_mutex, NULL) != 0)
			return (1);
		fork[i].n = i;
	}
	return (0);
}

/* Initializes the philosohers and their respective mutexes */
int	init_philo(t_input input, t_fork *fork, t_main main, t_philo *philo)
{
	int			i;
	pthread_t	temp;

	i = -1;
	while (++i < input.n_philo)
	{
		philo[i].n = i + 1;
		philo[i].eat_total = 0;
		philo[i].input = input;
		philo[i].left = &(fork[i]);
		philo[i].right = &(fork[(i + 1) % input.n_philo]);
		philo[i].main = main;
		philo[i].last_ate = main.start_time;
		if (pthread_mutex_init(&philo[i].philo_mutex, NULL) != 0)
			return (1);
		if (pthread_create(&temp, NULL, routine, &(philo[i])) != 0)
			return (1);
		pthread_detach(temp);
	}
	return (0);
}
