/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:10:55 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/16 19:03:50 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ft_usleep(long time)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_status(t_philo *philo, int state)
{
	long	time_passed;

	// if(read_bool(philo->program->global_sem->sem, &philo->program->end_of_program) == true)
	// 	return ;
	sem_wait(philo->program->global_sem->sem);
	time_passed = get_current_time() - philo->program->start_dinner;
	sem_post(philo->program->global_sem->sem);
	if (read_bool(philo->meal_sem->sem, &philo->is_full) == true)
		return ;
	sem_wait(philo->local_sem->sem);
	if (state == F_FORK && !end_of_dinner(philo->program))
		printf("%-6ld %d has taken a fork\n", time_passed, philo->id);
	if (state == S_FORK && !end_of_dinner(philo->program))
		printf("%-6ld %d has taken a fork\n", time_passed, philo->id);
	if (state == EAT && !end_of_dinner(philo->program))
		printf("%-6ld %d is eating\n", time_passed, philo->id);
	if (state == SLEEP && !end_of_dinner(philo->program))
		printf("%-6ld %d is sleeping\n", time_passed, philo->id);
	if (state == THINK && !end_of_dinner(philo->program))
		printf("%-6ld %d is thinking\n", time_passed, philo->id);
	if (state == DIE)
		printf("%-6ld %d died\n", time_passed, philo->id);
	sem_post(philo->local_sem->sem);
}

static void	close_unlink(t_named_semaphores *sem, bool mode)
{
	if (!sem || !sem->sem || !sem->name)
	{
		if (sem)
			free(sem);
		return ;
	}
	sem_close(sem->sem);
	if (mode)
		sem_unlink(sem->name);
	free(sem->name);
	free(sem);
}

static void	unlink_semaphores(t_program *data, bool mode)
{
	close_unlink(data->die_sem, mode);
	close_unlink(data->forks_sem, mode);
	close_unlink(data->global_sem, mode);
	close_unlink(data->end_prog_sem, mode);
	close_unlink(data->philos.local_sem, mode);
	close_unlink(data->philos.meal_sem, mode);
	close_unlink(data->philos.value_sem, mode);
}

void	clean_up(t_program *data, unsigned int exit_num, bool mode)
{
	unlink_semaphores(data, mode);
	free(data->pids);
	// free(data);
	exit(exit_num);
}
