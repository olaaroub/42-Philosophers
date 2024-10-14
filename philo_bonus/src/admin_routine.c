/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:39:33 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/05 19:16:42 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_dead_flag(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	long	last_eating_time;

	if (read_bool(&philo->philo_mtx, &philo->is_full) == true)
		return (0);
	last_eating_time = read_long(&philo->philo_mtx, &philo->last_eating_time);
	time_passed = get_current_time() - last_eating_time;
	time_to_die = philo->program->time_to_die;
	if (time_passed > time_to_die)
		return (1);
	return (0);
}

void	*admin_routine(void *param)
{
	t_program	*data;
	int			i;

	data = (t_program *)param;
	while(get_current_time() < data->start_dinner)
		usleep(500);
	ft_usleep(data->time_to_die - 10);
	while (!end_of_dinner(data) && !all_philos_full(data))
	{
		i = -1;
		while ((++i < data->philo_nbr && !end_of_dinner(data))
			&& !all_philos_full(data))
		{
			if (check_dead_flag(data->philos + i) == true
				&& !all_philos_full(data))
			{
				set_bool(&data->data_mutex, &data->end_of_program, true);
				print_status(data->philos + i, DIE);
			}
		}
	}
	return (NULL);
}
