/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:01:58 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/15 18:15:10 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

long	read_long(t_mtx *data_mutex, long *value)
{
	long	res;

	pthread_mutex_lock(data_mutex);
	res = *value;
	pthread_mutex_unlock(data_mutex);
	return (res);
}

bool	read_bool(t_mtx *data_mutex, bool *value)
{
	bool	res;

	pthread_mutex_lock(data_mutex);
	res = *value;
	pthread_mutex_unlock(data_mutex);
	return (res);
}

void	set_long(t_mtx *data_mutex, long *variable, long new_val)
{
	pthread_mutex_lock(data_mutex);
	*variable = new_val;
	pthread_mutex_unlock(data_mutex);
}

void	set_bool(t_mtx *data_mutex, bool *variable, bool new_val)
{
	pthread_mutex_lock(data_mutex);
	*variable = new_val;
	pthread_mutex_unlock(data_mutex);
}

bool	end_of_dinner(t_program *data)
{
	bool	status;

	status = read_bool(&data->global_sem, &data->end_of_program);
	return (status);
}

void	increment(t_mtx *data_mutex, long *variable)
{
	pthread_mutex_lock(data_mutex);
	*variable = *variable + 1;
	pthread_mutex_unlock(data_mutex);
}