/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_getters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:12:25 by schuah            #+#    #+#             */
/*   Updated: 2022/08/09 21:26:19 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_time(struct timeval old, void *timezone)
{
	static struct timeval	time;

	gettimeofday(&time, timezone);
	return (((time.tv_sec - old.tv_sec) * 1000)
		+ ((time.tv_usec - old.tv_usec) / 1000));
}

struct timeval	get_starttime(void *timezone)
{
	struct timeval	time;

	gettimeofday(&time, timezone);
	return (time);
}

void	get_message(t_philo *philo, int i, char *str)
{
	pthread_mutex_lock(&philo->main.write_mutex);
	printf("%d\t %d %s\n", get_time(philo->main.start_time, NULL),
		i, str);
	pthread_mutex_unlock(&philo->main.write_mutex);
}
