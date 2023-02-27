/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosophizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:01:15 by schuah            #+#    #+#             */
/*   Updated: 2023/02/24 16:22:21 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Puts the forks into the philosophers' respective hands */
static void	put_fork_in_hand(t_philo *philo, t_fork **left, t_fork **right)
{
	*left = philo->right;
	*right = philo->left;
	if (philo->left->n < philo->right->n)
	{
		*left = philo->left;
		*right = philo->right;
	}
}

/* Calculates and updates the last time the philosopher ate
** based on eating time & sleeping time */
static void	calculate_time(t_philo *philo, int sleeping)
{
	philo->last_ate.tv_sec += philo->input.eat_time * 1000;
	if (philo->last_ate.tv_usec >= 100000)
	{
		philo->last_ate.tv_sec++;
		philo->last_ate.tv_usec -= 100000;
	}
	if (sleeping)
	{
		philo->last_ate.tv_sec += philo->input.sleep_time * 1000;
		if (philo->last_ate.tv_usec >= 100000)
		{
			philo->last_ate.tv_sec++;
			philo->last_ate.tv_usec -= 100000;
		}
	}
}

/* Locks the forks when the philosopher is eating, unlocks when finished */
static void	eat(t_philo *philo, int sleeping)
{
	t_fork	*left;
	t_fork	*right;

	put_fork_in_hand(philo, &left, &right);
	pthread_mutex_lock(&(left->fork_mutex));
	get_message(philo, philo->n, "has taken a fork", "\033[1;36m");
	pthread_mutex_lock(&(right->fork_mutex));
	get_message(philo, philo->n, "has taken a fork", "\033[1;36m");
	get_message(philo, philo->n, "is eating", "\033[1;32m");
	pthread_mutex_lock(&(philo->philo_mutex));
	philo->eat_total++;
	pthread_mutex_unlock(&(philo->philo_mutex));
	usleep(philo->input.eat_time * 1000);
	pthread_mutex_lock(&(philo->philo_mutex));
	calculate_time(philo, sleeping);
	pthread_mutex_unlock(&(philo->philo_mutex));
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(right->fork_mutex));
}

/* The routine each philosopher has to go through for the rest of their lives */
void	*routine(void *arg)
{
	if (((t_philo *)arg)->n % 2 == 0)
		usleep(2500);
	eat((t_philo *)arg, 0);
	while (1)
	{
		get_message((t_philo *)arg, ((t_philo *)arg)->n,
			"is sleeping", "\033[1;30m");
		usleep(((t_philo *)arg)->input.sleep_time * 1000);
		get_message((t_philo *)arg, ((t_philo *)arg)->n,
			"is thinking", "\033[1;33m");
		eat((t_philo *)arg, 1);
	}
	return (NULL);
}
