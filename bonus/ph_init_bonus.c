/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:36:58 by schuah            #+#    #+#             */
/*   Updated: 2022/08/15 16:37:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_arg(t_input *input, int ac, char **av)
{
	input->n_philo = ft_atoi(av[1]);
	input->death_time = ft_atoi(av[2]);
	input->eat_time = ft_atoi(av[3]);
	input->sleep_time = ft_atoi(av[4]);
	input->eat_req = 0;
	input->eat_max = 0;
	if (ac == 6)
	{
		input->eat_max = ft_atoi(av[5]);
		input->eat_req = 1;
	}
}
