/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:11:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/13 20:15:06 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static void	give_forks(t_philo *philo, t_mtx *forks, int philo_position)
// {
// 	long	nbr_philos;

// 	nbr_philos = philo->program->philo_nbr;
// 	philo->first_fork = &forks[(philo_position + 1) % nbr_philos];
// 	philo->second_fork = &forks[philo_position];
// 	if (philo->id % 2 == 0)
// 	{
// 		philo->first_fork = &forks[philo_position];
// 		philo->second_fork = &forks[(philo_position + 1) % nbr_philos];
// 	}
// }

static void	init_philo(t_program *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	// while (++i < data->philo_nbr)
	// {
	// 	philo = data->philos + i;
	// 	philo->id = i + 1;
	// 	philo->is_full = 0;
	// 	philo->meals_eaten = 0;
	// 	philo->program = data;
	// 	// give_forks(philo, data->forks, i);
	// }
}

void	init_data(t_program *data)
{
	int	i;

	i = -1;
	// open_semaphores(data, DATA);
	init_philo(data);
}
