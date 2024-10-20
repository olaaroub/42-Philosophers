/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:39:33 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/20 17:47:00 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

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
// bool philo_eating(t_philo *philo)
// {

// }

void	*admin_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	// while(get_current_time() < data->->start_dinner)
	// 	usleep(500);
	long time_to_die = read_long(philo->local_sem->sem,  &philo->program->time_to_die);
	if(time_to_die - 10 > 0)
		ft_usleep(time_to_die - 10);
	else
		ft_usleep(time_to_die);
	while (!end_of_dinner(philo->program))
	{
		if(read_bool(philo->local_sem->sem, &philo->is_full) == true)
			break ;
		if (check_dead_flag(philo) == true)
		{
			set_bool(philo->program->global_sem->sem, &philo->program->end_of_program, true);
			sem_wait(philo->program->die_sem->sem);
			usleep(1000);
			print_status(philo, DIE);
		}
	}
	return (NULL);
}
