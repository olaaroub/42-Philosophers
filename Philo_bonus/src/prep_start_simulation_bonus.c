/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_start_simulation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:21:28 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/20 18:18:29 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

// static void	*handle_one_philo(void *param)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)param;
// 	// check_threads(philo->program);
// 	set_long(&philo->philo_mtx, &philo->last_eating_time, get_current_time());
// 	print_status(philo, F_FORK);
// 	while (!end_of_dinner(philo->program))
// 		ft_usleep(0);
// 	return (NULL);
// }

// static void	think_routine(t_philo *philo)
// {
// 	print_status(philo, THINK);
// 	if((philo->program->philo_nbr % 2 != 0))
// 		usleep(1000);
// }

// static void	take_fork(t_philo *philo)
// {
// 	sem_wait(philo->program->forks_sem->sem);
// 	// if(check_death(philo->program->die_sem->sem, philo->program->global_sem->sem) != 0)
// 	print_status(philo, F_FORK);
// }

static void	eat_routine(t_philo *philo)
{
	sem_wait(philo->program->forks_sem->sem);
	print_status(philo, F_FORK);
	sem_wait(philo->program->forks_sem->sem);
	print_status(philo, F_FORK);
	// take_fork(philo);
	// take_fork(philo);
	// set_bool(philo->meal_sem->sem, &philo->is_eating, true);
	set_long(philo->value_sem->sem, &philo->last_eating_time,  get_current_time());
	print_status(philo, EAT);
	ft_usleep(philo->program->time_to_eat);
	sem_post(philo->program->forks_sem->sem);
	sem_post(philo->program->forks_sem->sem);
	philo->meals_eaten++;
	if (philo->program->num_of_meals > 0
		&& philo->meals_eaten == philo->program->num_of_meals)
		set_bool(philo->meal_sem->sem, &philo->is_full, true);
}

static void	*start_simulation(t_philo *philo)
{
	if(open_sems(philo))
		clean_up(philo->program, 1, 0);
	while (get_current_time() < philo->program->start_dinner)
		usleep(500);
	if (philo->id % 2 == 0)
		usleep(500);
	pthread_create(&philo->thread, NULL, &admin_routine, philo);
	philo->last_eating_time = get_current_time();
	while (!end_of_dinner(philo->program))
	{
		// if(philo->program->die_sem->sem->__align == 0 || philo->program->die_sem->sem->__align > 1)
		// 	break ;
		if (philo->is_full == true)
			break ;
		eat_routine(philo);
		print_status(philo, SLEEP);
		ft_usleep(philo->program->time_to_sleep);
		print_status(philo, THINK);
		if((philo->program->philo_nbr % 2 != 0))
			usleep(1000);
		// think_routine(philo);
	}
	pthread_join(philo->thread, NULL);
	clean_up(philo->program, 0, 0);
	return NULL;
}

static void	*check_wait(void *data)
{
	t_wait	*wait;
	int		x;

	x = 0;
	wait = data;
	while (read_bool(wait->stop, &wait->stop_flag))
	{
		if (wait->died->__align == 0 || wait->died->__align > 1)
		{
			usleep(2000);
			while (x < wait->pids_num)
			{
				kill(wait->pids[x], SIGKILL);
				x++;
			}
			break ;
		}
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
	data->start_dinner = get_current_time() + (data->philo_nbr * 15);
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
	set_bool(data->end_prog_sem->sem, &wait.stop_flag, 0);
	pthread_join(thread, NULL);
}
