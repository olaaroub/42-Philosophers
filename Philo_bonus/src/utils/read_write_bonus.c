/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:01:58 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/02 20:42:34 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

long	read_long(sem_t *sem, long *value)
{
	long	res;

	sem_wait(sem);
	res = *value;
	sem_post(sem);
	return (res);
}

bool	read_bool(sem_t *sem, bool *value)
{
	bool	res;

	sem_wait(sem);
	res = *value;
	sem_post(sem);
	return (res);
}

void	set_long(sem_t *sem, long *variable, long new_val)
{
	sem_wait(sem);
	*variable = new_val;
	sem_post(sem);
}

void	set_bool(sem_t *sem, bool *variable, bool new_val)
{
	sem_wait(sem);
	*variable = new_val;
	sem_post(sem);
}

long	check_death(sem_t *from, sem_t *lock)
{
	long	res;

	res = 0;
	sem_wait(lock);
	res = from->__align;
	sem_post(lock);
	return (res);
}
