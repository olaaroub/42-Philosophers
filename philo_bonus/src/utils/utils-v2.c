/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:10:55 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/15 17:12:54 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	check_threads(t_program *data)
{
	while (!read_bool(&data->data_mutex, &data->threads_ready))
		;
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return(printf("gettimeofday() error \n"), -1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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
bool	all_philos_full(t_program *data)
{
	long	nbr;

	nbr = read_long(&data->data_mutex, &data->all_full);
	if (nbr == data->philo_nbr)
		return (1);
	return (false);
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
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->philos);
	free(data->forks);
}
