/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:36:58 by schuah            #+#    #+#             */
/*   Updated: 2023/02/28 16:46:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Initializes the values into the struct based on the user input */
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

/* Initializes the semaphore needed for the routine */
static int	init_sema(t_philo *philo, t_input input)
{
	sem_unlink("fork");
	sem_unlink("sema");
	sem_unlink("read");
	sem_unlink("write");
	philo->fork = sem_open("fork", O_CREAT, S_IRWXU, input.n_philo);
	if (philo->fork == SEM_FAILED)
		return (-1);
	philo->sema = sem_open("sema", O_CREAT, S_IRWXU, 0);
	if (philo->sema == SEM_FAILED)
		return (-1);
	philo->read = sem_open("read", O_CREAT, S_IRWXU, 1);
	if (philo->read == SEM_FAILED)
		return (-1);
	philo->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	if (philo->write == SEM_FAILED)
		return (-1);
	return (0);
}

/* Initializes the philosopher's value and starts the routine */
int	init_philo(t_philo *philo, t_input input)
{
	if (init_sema(philo, input) == -1)
		return (1);
	philo->start_time = get_starttime(NULL);
	philo->last_ate = philo->start_time;
	philo->input = input;
	philo->n = 1;
	while (philo->n <= input.n_philo)
	{
		philo->pid[philo->n] = fork();
		if (philo->pid[philo->n] == -1)
			return (1);
		if (philo->pid[philo->n] == 0)
			routine(philo);
		philo->n++;
	}
	check_stomach(philo, input);
	finish_and_exit(philo);
	return (0);
}
