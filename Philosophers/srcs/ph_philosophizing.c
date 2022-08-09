/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosophizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:01:15 by schuah            #+#    #+#             */
/*   Updated: 2022/08/09 20:47:13 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* DONE CHECKING */
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

/* DONE CHECKING */
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

/* DONE CHECKING */
static void	eat(t_philo *philo, int sleeping)
{
	t_fork	*left;
	t_fork	*right;

	put_fork_in_hand(philo, &left, &right);
	pthread_mutex_lock(&(left->fork_mutex));
	get_message(philo, philo->n, "has taken a fork");
	pthread_mutex_lock(&(right->fork_mutex));
	get_message(philo, philo->n, "has taken a fork");
	get_message(philo, philo->n, "is eating");
	usleep(philo->input.eat_time * 1000);
	pthread_mutex_lock(&(philo->philo_mutex));
	printf("PN: %d ATE: %d\n", philo->n, philo->eat_total);
	philo->eat_total++;
	calculate_time(philo, sleeping);
	pthread_mutex_unlock(&(philo->philo_mutex));
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(right->fork_mutex));
}

/* DONE CHECKING */
void	*routine(void *arg)
{
	if (((t_philo *)arg)->n % 2 == 0)
		usleep(2500);
	eat((t_philo *)arg, 0);
	get_message((t_philo *)arg, ((t_philo *)arg)->n, "is sleeping");
	usleep(((t_philo *)arg)->input.sleep_time * 1000);
	get_message((t_philo *)arg, ((t_philo *)arg)->n, "is thinking");
	while (1)
	{
		eat((t_philo *)arg, 1);
		get_message((t_philo *)arg, ((t_philo *)arg)->n, "is sleeping");
		usleep(((t_philo *)arg)->input.sleep_time * 1000);
		get_message((t_philo *)arg, ((t_philo *)arg)->n, "is thinking");
	}
	return (NULL);
}
