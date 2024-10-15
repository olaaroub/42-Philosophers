/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:10:55 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/15 18:07:30 by olaaroub         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->program->data_mutex);
	time_passed = get_current_time() - philo->program->start_dinner;
	pthread_mutex_unlock(&philo->program->data_mutex);
	if (read_bool(&philo->program->data_mutex, &philo->is_full) == true)
		return ;
	pthread_mutex_lock(&philo->program->write_mutex);
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
	pthread_mutex_unlock(&philo->program->write_mutex);
}

void	close_unlink(t_named_semaphores *sem, bool mode)
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

void	unlink_semaphores(t_program *data, bool mode)
{
	close_unlink(data->die_sem, mode);
	close_unlink(data->forks_sem, mode);
	close_unlink(data->global_sem, mode);
	close_unlink(data->end_prog_sem, mode);
	close_unlink(data->philos.is_full, mode);
	// close_unlink(data->philos.meal, mode);
	close_unlink(data->philos.local_sem, mode);
}

void	clean_up(t_program *data, unsigned int exit_num, bool mode)
{
	unlink_semaphores(data, mode);
	free(data->pids);
	// free(data);
	exit(exit_num);
}
