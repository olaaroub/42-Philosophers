/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:42:22 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/02 20:53:27 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

long	ft_atol(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > INT_MAX)
			return (res);
	}
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 && *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (s1 - s2);
}

void	exit_when_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

void	increment(t_mtx *data_mutex, long *variable)
{
	pthread_mutex_lock(data_mutex);
	*variable = *variable + 1;
	pthread_mutex_unlock(data_mutex);
}
