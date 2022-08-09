/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_checkstate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:32:05 by schuah            #+#    #+#             */
/*   Updated: 2022/08/09 20:28:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_is_dead(t_philo *philo)
{
	struct timeval	curr;

	curr = get_starttime(NULL);
	pthread_mutex_lock(&philo->philo_mutex);
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

/* DONE CHECKIN */
int	check_state(t_philo *philo, t_input input)
{
	int	i;
	int	ongoing;

	while (1)
	{
		ongoing = 0;
		i = -1;
		while (++i < input.n_philo)
		{
			pthread_mutex_lock(&philo[i].philo_mutex);
			if (input.eat_req && philo->eat_total > input.eat_max - 1)
				ongoing = 1;
			pthread_mutex_unlock(&philo[i].philo_mutex);
			if (check_is_dead(&philo[i]))
			{
				get_message(philo, philo->n, "died");
				return (1);
			}
		}
		if (ongoing)
			return (0);
	}
	return (0);
}
