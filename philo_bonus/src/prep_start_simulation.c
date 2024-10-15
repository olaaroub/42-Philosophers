/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_start_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:21:28 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/15 18:12:36 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*handle_one_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	// check_threads(philo->program);
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
	// else
	// 	usleep(30);
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

void	*start_simulation(t_philo *philo)
{
	if(open_sems(philo))
		clean_up(philo->program, 1, 0);
	while (get_current_time() < philo->program->start_dinner)
		usleep(500);
	pthread_create(&philo->thread, NULL, &admin_routine, philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	set_long(&philo->local_sem, &philo->last_eating_time, get_current_time());
	while (!end_of_dinner(philo->program))
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
	pthread_t thread;
	t_wait wait;
	int	i;

	i = -1;
	// else if (data->philo_nbr == 1)
	// 	pthread_create(&data->philos[0].thread_id, NULL, handle_one_philo,
	// 		&data->philos[0]);
	// else
	// {
	data->start_dinner = get_current_time() + (data->philo_nbr * 25);
	while (++i < data->philo_nbr)
	{
		data->philos.id = i + 1;
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			start_simulation(&data->philos);
	}
	wait.died = data->die_sem->sem;
	wait.stop = data->end_prog_sem->sem;
	wait.stop_flag = true;
	wait.pids = data->pids;
	wait.pids_num = data->philo_nbr;
	pthread_create(&thread, NULL, &check_wait, &wait);
	while(waitpid(-1, NULL, 0) != -1)
		;
	set_bool(&data->end_prog_sem->sem, &wait.stop_flag, 0);
	pthread_join(thread, NULL);
}
