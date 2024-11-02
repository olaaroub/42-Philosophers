/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:31 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/02 20:43:28 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

int	open_sems(t_philo *philo)
{
	philo->local_sem = malloc(sizeof(t_named_semaphores));
	if (!philo->local_sem)
		return (-1);
	philo->meal_sem = malloc(sizeof(t_named_semaphores));
	if (!philo->meal_sem)
		return (-1);
	philo->value_sem = malloc(sizeof(t_named_semaphores));
	if (!philo->value_sem)
		return (-1);
	if (ft_sem_open(&philo->local_sem, "local", philo->id))
		return (-1);
	if (ft_sem_open(&philo->meal_sem, "meal", philo->id))
		return (-1);
	if (ft_sem_open(&philo->value_sem, "value", philo->id))
		return (-1);
	return (0);
}

bool	end_of_dinner(t_program *data)
{
	long	x;

	x = check_death(data->die_sem->sem, data->global_sem->sem);
	if (x == 0 || x > 1)
		return (true);
	else
		return (false);
}

void	exit_when_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}
