/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosophizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:10:16 by schuah            #+#    #+#             */
/*   Updated: 2022/08/16 15:32:40 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Prints and exits the program if the philosopher is dead */
static void	*check_death(void *args)
{
	int		now;

	while (1)
	{
		sem_wait(((t_philo *)args)->read);
		now = get_time(((t_philo *)args)->last_ate, NULL);
		sem_post(((t_philo *)args)->read);
		if (now > ((t_philo *)args)->input.death_time)
		{
			get_message((t_philo *)args, ((t_philo *)args)->n, "died");
			break ;
		}
	}
	finish_and_exit((t_philo *)args);
	return (NULL);
}

/* Resets philosopher's last ate time and reduce its max eat by one each eat */
static void	eat(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	sem_wait(philo->read);
	philo->last_ate = now;
	sem_post(philo->read);
	get_message(philo, philo->n, "is eating");
	usleep(philo->input.eat_time * 1000);
	if (philo->input.eat_req)
	{
		philo->input.eat_max--;
		if (philo->input.eat_max <= 0)
			sem_post(philo->sema);
	}
}

/* The routine each philosopher has to go through for the rest of their lives */
void	routine(t_philo *philo)
{
	if (philo->n % 2 == 0)
		usleep(2500);
	pthread_create(&philo->death_thread, NULL, &check_death, philo);
	pthread_detach(philo->death_thread);
	while (1)
	{
		sem_wait(philo->fork);
		get_message(philo, philo->n, "has taken a fork");
		sem_wait(philo->fork);
		get_message(philo, philo->n, "has taken a fork");
		eat(philo);
		sem_post(philo->fork);
		sem_post(philo->fork);
		get_message(philo, philo->n, "is sleeping");
		usleep(philo->input.sleep_time * 1000);
		get_message(philo, philo->n, "is thinking");
	}
}

/* Waits when max_eat has reached <= 0, then finish and exit per philosopher */
void	check_stomach(t_philo *philo, t_input input)
{
	int		i;

	if (philo->input.eat_req)
	{
		philo->stomach_process = fork();
		if (philo->stomach_process != 0)
			return ;
		i = -1;
		while (i++ < input.n_philo)
			sem_wait(philo->sema);
		sem_wait(philo->write);
		finish_and_exit(philo);
	}
}

/* Finishes the simulation and exits the program cleanly */
void	finish_and_exit(t_philo *philo)
{
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
	free(philo->pid);
	sem_close(philo->fork);
	sem_close(philo->sema);
	sem_close(philo->read);
	sem_close(philo->write);
	exit(0);
}
