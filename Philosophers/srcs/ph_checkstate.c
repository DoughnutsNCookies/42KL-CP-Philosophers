/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_checkstate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:32:05 by schuah            #+#    #+#             */
/*   Updated: 2022/08/15 15:51:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns 1 if the philosopher is dead, otherwise returns 0 */
static int	check_is_dead(t_philo *philo)
{
	struct timeval	curr;

	pthread_mutex_lock(&philo->philo_mutex);
	curr = get_starttime(NULL);
	if ((curr.tv_sec - philo->last_ate.tv_sec) * 1000
		+ (curr.tv_usec - philo->last_ate.tv_usec + 500) / 1000
		>= philo->input.death_time)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (0);
}

/* Checks the state of the philosopher during the simulation */
int	check_state(t_philo *philo)
{
	int	i;
	int	end;

	while (1)
	{
		end = 0;
		i = 0;
		while (i < philo->input.n_philo)
		{
			pthread_mutex_lock(&(philo->philo_mutex));
			if (philo->input.eat_req)
				if (philo->eat_total > philo->input.eat_max)
					end = 1;
			pthread_mutex_unlock(&(philo->philo_mutex));
			if (check_is_dead(&philo[i]))
			{
				get_message(philo, philo->n, "died");
				return (1);
			}
			i++;
		}
		if (end)
			return (0);
	}
	return (0);
}
