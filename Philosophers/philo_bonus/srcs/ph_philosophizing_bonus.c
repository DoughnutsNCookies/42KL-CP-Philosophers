/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosophizing_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:10:16 by schuah            #+#    #+#             */
/*   Updated: 2023/03/01 18:10:02 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Prints and exits the program if the philosopher is dead */
static void	*check_death(void *args)
{
	int		now;
	t_philo	*philo;

	philo = args;
	while (1)
	{
		ft_usleep(philo->input.death_time / 2);
		sem_wait(philo->read);
		now = get_time(philo->last_ate, NULL);
		sem_post(philo->read);
		if (now > philo->input.death_time)
		{
			get_message((t_philo *)args, philo->n, "died");
			break ;
		}
	}
	finish_and_exit(philo);
	return (NULL);
}

/* Resets philosopher's last ate time and reduce its max eat by one each eat */
static void	eat(t_philo *philo)
{
	sem_wait(philo->read);
	gettimeofday(&philo->last_ate, NULL);
	sem_post(philo->read);
	get_message(philo, philo->n, "is eating");
	ft_usleep(philo->input.eat_time);
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
	char	*sem_name;
	char	*philo_id;

	if (philo->n % 2 == 0)
		ft_usleep(500);
	philo_id = ft_itoa(philo->n);
	sem_name = ft_strjoin("read", philo_id);
	create_sema(philo->read, sem_name, 1);
	free(philo_id);
	free(sem_name);
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
		ft_usleep(philo->input.sleep_time);
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
	free(philo->pid);
	kill(0, SIGINT);
}
