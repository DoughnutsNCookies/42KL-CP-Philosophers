/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getters_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:39:02 by schuah            #+#    #+#             */
/*   Updated: 2022/08/15 21:32:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

struct timeval	get_starttime(void *timezone)
{
	struct timeval	new;

	gettimeofday(&new, timezone);
	return (new);
}

int	get_time(struct timeval old, void *timezone)
{
	static struct timeval	time;

	gettimeofday(&time, timezone);
	return (((time.tv_sec - old.tv_sec) * 1000)
		+ ((time.tv_usec - old.tv_usec) / 1000));
}

/* Prints out messages based on events */
void	get_message(t_philo *philo, int i, char *str)
{
	sem_wait(philo->write);
	printf("%d\t %d %s\n", get_time(philo->start_time, NULL),
		i, str);
	sem_post(philo->write);
}