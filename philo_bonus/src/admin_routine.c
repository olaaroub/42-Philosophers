/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:39:33 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/16 19:12:05 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_dead_flag(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	long	last_eating_time;

	if (read_bool(philo->local_sem->sem, &philo->is_full) == true)
		return (0);
	last_eating_time = read_long(philo->value_sem->sem, &philo->last_eating_time);
	time_passed = get_current_time() - last_eating_time;
	time_to_die = philo->program->time_to_die;
	if (time_passed > time_to_die)
		return (1);
	return (0);
}

void	*admin_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	// while(get_current_time() < data->start_dinner)
	// 	usleep(500);
	ft_usleep(philo->program->time_to_die - 10);
	while (!end_of_dinner(philo->program) && !read_bool(philo->local_sem->sem, &philo->is_full))
	{
		if (check_dead_flag(philo) == true)
		{
			set_bool(philo->program->global_sem->sem, &philo->program->end_of_program, true);
			sem_wait(philo->program->die_sem->sem);
			usleep(3000);
			print_status(philo, DIE);
		}
	}
	return (NULL);
}
