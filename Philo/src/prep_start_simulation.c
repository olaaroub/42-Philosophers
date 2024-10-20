/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_start_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:21:28 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/20 16:40:13 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*handle_one_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	check_threads(philo->program);
	set_long(&philo->philo_mtx, &philo->last_eating_time, get_current_time());
	print_status(philo, F_FORK);
	while (!end_of_dinner(philo->program))
		ft_usleep(0);
	return (NULL);
}

void	think_routine(t_philo *philo)
{
	print_status(philo, THINK);
	if((philo->program->philo_nbr % 2 != 0))
		usleep(1000);
}

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, F_FORK);
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, S_FORK);
	set_long(&philo->philo_mtx, &philo->last_eating_time, get_current_time());
	print_status(philo, EAT);
	ft_usleep(philo->program->time_to_eat);
	philo->meals_eaten++;
	if (philo->program->num_of_meals > 0
		&& philo->meals_eaten == philo->program->num_of_meals)
	{
		set_bool(&philo->philo_mtx, &philo->is_full, true);
		increment(&philo->program->data_mutex, &philo->program->all_full);
	}
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*start_simulation(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (get_current_time() < philo->program->start_dinner)
		usleep(500);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_eating_time = get_current_time();
	while (!end_of_dinner(philo->program) && !all_philos_full(philo->program))
	{
		if (philo->is_full == true)
			break ;
		eat_routine(philo);
		print_status(philo, SLEEP);
		ft_usleep(philo->program->time_to_sleep);
		think_routine(philo);
	}
	return (NULL);
}

void	prepare_simulation(t_program *data)
{
	int	i;

	i = -1;
	if (data->num_of_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		pthread_create(&data->philos[0].thread_id, NULL, handle_one_philo,
			&data->philos[0]);
	else
	{
		data->start_dinner = (get_current_time() + data->philo_nbr * 10);
		while (++i < data->philo_nbr)
			pthread_create(&data->philos[i].thread_id, NULL, start_simulation,
				&data->philos[i]);
	}
	pthread_create(&data->admin_thread, NULL, admin_routine, data);
	set_bool(&data->data_mutex, &data->threads_ready, true);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_join(data->philos[i].thread_id, NULL);
	set_bool(&data->data_mutex, &data->end_of_program, true);
	pthread_join(data->admin_thread, NULL);
}
