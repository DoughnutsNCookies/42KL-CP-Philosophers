/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_libft_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:45:45 by schuah            #+#    #+#             */
/*   Updated: 2023/03/01 17:53:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Checks whether the character is a space */
static int	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

/* Converts a string of numbers into an integer */
long	ft_atoi(const char *str)
{
	int		i;
	int		value;
	long	number;
	int		counter;

	i = 0;
	value = 1;
	number = 0;
	counter = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			value = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i++] - 48);
		counter++;
	}
	return (number * value);
}

/* Converts numbers into a string */
char	*ft_itoa(int n)
{
	size_t		i;
	long int	an;
	char		*output;

	an = n;
	i = (n <= 0);
	while (n != 0 && ++i > 0)
		n = n / 10;
	output = malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (NULL);
	if (an < 0)
		output[0] = '-';
	if (an < 0)
		an *= -1;
	output[i--] = '\0';
	if (an == 0)
		output[0] = 48;
	while (an)
	{
		output[i--] = (an % 10) + '0';
		an /= 10;
	}
	return (output);
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/* Joins two strings into one */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	output = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		output[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		output[j++] = s2[i++];
	output[j] = '\0';
	return (output);
}

/* Returns 1 if the string is a digit, otherwise returns 0 */
int	str_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

/* A more accurate usleep */
void	ft_usleep(int millisec)
{
	struct timeval	start;
	struct timeval	now;
	// int				diff;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(500);
		gettimeofday(&now, NULL);
		// diff = ((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000);
		if (((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000) >= millisec)
			break ;
	}
}