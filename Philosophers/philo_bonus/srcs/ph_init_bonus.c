/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:36:58 by schuah            #+#    #+#             */
/*   Updated: 2023/03/01 18:05:59 by schuah           ###   ########.fr       */
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
	input->eat_req = (ac == 6);
	input->eat_max = 0;
	if (ac == 6)
		input->eat_max = ft_atoi(av[5]);
}

/* Unlinks, closes and reopen a new semaphore */
int	create_sema(sem_t *sem, char *name, int count)
{
	sem_unlink(name);
	sem_close(sem);
	sem = sem_open(name, O_CREAT, S_IRWXU, count);
	return (sem == SEM_FAILED);
}

/* Initializes the semaphore needed for the routine */
static int	init_sema(t_philo *philo, t_input input)
{
	int	ret;

	ret = 0;
	ret += create_sema(philo->fork, "fork", input.n_philo);
	ret += create_sema(philo->sema, "sema", 0);
	ret += create_sema(philo->write, "write", 1);
	return (ret);
}

/* Initializes the philosopher's value and starts the routine */
int	init_philo(t_philo *philo, t_input input)
{
	if (init_sema(philo, input))
		return (1);
	gettimeofday(&philo->start_time, NULL);
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
