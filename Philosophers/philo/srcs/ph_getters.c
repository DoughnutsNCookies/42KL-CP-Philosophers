/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:12:25 by schuah            #+#    #+#             */
/*   Updated: 2022/08/16 14:02:18 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Gets the current time in int form */
static int	get_time(struct timeval old, void *timezone)
{
	static struct timeval	time;

	gettimeofday(&time, timezone);
	return (((time.tv_sec - old.tv_sec) * 1000)
		+ ((time.tv_usec - old.tv_usec) / 1000));
}

/* Gets the current time in struct timeval form */
struct timeval	get_starttime(void *timezone)
{
	struct timeval	time;

	gettimeofday(&time, timezone);
	return (time);
}

/* Prints out messages based on events */
void	get_message(t_philo *philo, int i, char *str)
{
	pthread_mutex_lock(&philo->main.write_mutex);
	printf("%d\t %d %s\n", get_time(philo->main.start_time, NULL),
		i, str);
	pthread_mutex_unlock(&philo->main.write_mutex);
}
