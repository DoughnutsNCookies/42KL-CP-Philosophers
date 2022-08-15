/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosophizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:10:16 by schuah            #+#    #+#             */
/*   Updated: 2022/08/15 21:44:45 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Try Change template and remove usleep */
static void	*check_death(void *args)
{
	int		now;
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->read);
		now = get_time(philo->last_ate, NULL);
		sem_post(philo->read);
		if (time > philo->input.death_time)
		{
			get_message(philo, philo->n, "died\n");
			break ;
		}
		usleep(500);
	}
	exit(0);
}

static void	eat(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	sem_wait(philo->read);
	philo->last_ate = now;
	sem_post(philo->read);
	get_message(philo, philo->n, "is eating\n");
	usleep(philo->input.eat_time * 1000);
	if (philo->input.eat_req)
	{
		philo->input.eat_max--;
		if (philo->input.eat_max <= 0)
			sem_post(philo->sema);
	}
}

void	routine(t_philo *philo)
{
	if (philo->n % 2 == 0)
		usleep(2500);
	pthread_create(&philo->death_thread, NULL, &check_death, philo);
	pthread_detach(philo->death_thread);
	while (1)
	{
		sem_wait(philo->fork);
		get_message(philo, philo->n, "has taken a fork\n");
		sem_wait(philo->fork);
		get_message(philo, philo->n, "has taken a fork\n");
		eat(philo);
		sem_post(philo->fork);
		sem_post(philo->fork);
		get_message(philo, philo->n, "is sleeping\n");
		usleep(philo->input.sleep_time * 1000);
		get_message(philo, philo->n, "is thinking\n");
	}
}
