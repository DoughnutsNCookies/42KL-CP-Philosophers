/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:29:15 by schuah            #+#    #+#             */
/*   Updated: 2023/02/24 16:15:37 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX 200

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_input
{
	int	n_philo;
	int	eat_req;
	int	eat_max;
	int	death_time;
	int	eat_time;
	int	sleep_time;
}	t_input;

typedef struct s_fork
{
	int				n;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_main
{
	struct timeval	start_time;
	pthread_mutex_t	write_mutex;
}	t_main;

typedef struct s_philo
{
	int				n;
	int				eat_total;
	struct s_input	input;
	t_fork			*left;
	t_fork			*right;
	struct s_main	main;
	pthread_mutex_t	philo_mutex;
	struct timeval	last_ate;
}	t_philo;

/* Libft */
long			ft_atoi(const char *str);
int				str_is_digit(char *str);

/* Initializing */
void			init_arg(t_input *input, int ac, char **av);
int				init_fork(t_input *input, t_fork *fork);
int				init_philo(t_input input, t_fork *fork,
					t_main main, t_philo *philo);

/* Getters */
struct timeval	get_starttime(void *timezone);
void			get_message(t_philo *philo, int i, char *str, char *color);
int				force_death(t_philo philo);

/* Checkers */
int				check_state(t_philo *philo);

/* Philosophizing */
void			*routine(void *arg);

#endif