/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:36:29 by schuah            #+#    #+#             */
/*   Updated: 2022/08/15 21:43:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define MAX 200

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_input
{
	int	n_philo;
	int	eat_req;
	int	eat_max;
	int	death_time;
	int	eat_time;
	int	sleep_time;
}	t_input;

typedef struct s_philo
{
	int				n;
	pid_t			*pid;
	sem_t			*fork;
	sem_t			*sema;
	sem_t			*read;
	sem_t			*write;
	t_input			input;
	pthread_t		death_thread;
	struct timeval	start_time;
	struct timeval	last_ate;
}	t_philo;

/* Libft */
long			ft_atoi(const char *str);
int				str_is_digit(char *str);

/* Initializing */
void			init_arg(t_input *input, int ac, char **av);
int				init_philo(t_philo *philo, t_input input);

/* Getters */
struct timeval	get_starttime(void *timezone);
int				get_time(struct timeval old, void *timezone);
void			get_message(t_philo *philo, int i, char *str);

#endif