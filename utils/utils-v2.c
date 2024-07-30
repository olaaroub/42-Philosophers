/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:10:55 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/30 13:36:49 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_threads(t_program *data)
{
	while (!read_bool(&data->get_mutex, &data->threads_ready))
		;
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		printf("gettimeofday() error \n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_status(t_philo *philo, int state)
{
	long	time_passed;

	time_passed = get_current_time() - philo->program->start_dinner;
	if (read_bool(&philo->program->get_mutex, &philo->is_full) == true)
		return ;
	pthread_mutex_lock(&philo->program->write_mutex);
	if (state == F_FORK && !end_of_dinner(philo->program))
		printf("%-6ld %d has taken first fork\n", time_passed, philo->id);
	if (state == S_FORK && !end_of_dinner(philo->program))
		printf("%-6ld %d has taken second fork\n", time_passed, philo->id);
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

void	clean_exit(t_program *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		pthread_mutex_destroy(&philo->philo_mtx);
	}
	pthread_mutex_destroy(&data->get_mutex);
	pthread_mutex_destroy(&data->set_mutex);
	free(data->philos);
	free(data->forks);
}
