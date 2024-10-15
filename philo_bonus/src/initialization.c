/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:11:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/15 17:10:31 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_philo(t_program *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
}

int program_sem_init(t_program *data)
{
	data->die_sem = malloc(sizeof(t_named_semaphores));
	if (!data->die_sem)
		return (-1);
	data->global_sem = malloc(sizeof(t_named_semaphores));
	if (!data->global_sem)
		return (free(data->die_sem), -1);
	data->forks_sem = malloc(sizeof(t_named_semaphores));
	if (!data->forks_sem)
		return (free(data->die_sem), free(data->global_sem), -1);
	data->pids = malloc(sizeof(int) * data->philo_nbr);
	if (!data->pids)
		return (free(data->die_sem), free(data->global_sem),
			free(data->forks_sem), -1);
	data->die_sem->sem = NULL;
	data->global_sem->sem = NULL;
	data->forks_sem->sem = NULL;
	data->die_sem->name = NULL;
	data->global_sem->name = NULL;
	data->forks_sem->name = NULL;
	return (0);
}

int sem_forks(t_named_semaphores **sem, char *name, int philo_nbr)
{
	(*sem)->name = name;
	sem_unlink(name);
	(*sem) = sem_open(name, O_CREAT | O_EXCL, 0644, philo_nbr);
	if ((*sem)->sem == SEM_FAILED)
	{
		printf("Failed to create semaphore\n");
		(*sem)->sem = NULL;
		return (-1);
	}
	return (0);
}

int ft_sem_open(t_named_semaphores **sem, char *name)
{
	(*sem)->name = name;
	sem_unlink(name);
	(*sem)->sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if ((*sem)->sem == SEM_FAILED)
	{
		printf("Failed to create semaphore\n");
		return (-1);
	}
	return (0);
}

void	init_data(t_program *data)
{
	if(!program_sem_init(data))
		exit_when_error("Error in sem_init !\n");
	memset(data->philos, 0, sizeof(t_philo));
	data->philos.program = data;
	if(sem_forks(&data->forks_sem, "forks_sem", data->philo_nbr))
		exit_when_error("sem_open faild\n");
	if(ft_sem_open(&data->die_sem, "die_sem"))
		exit_when_error("sem_open faild\n");
	if(ft_sem_open(&data->global_sem, "global_sem"))
		exit_when_error("sem_open faild\n");
	init_philo(data);
}
