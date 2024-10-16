/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:11:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/16 18:46:47 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int program_sem_init(t_program *data)
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
	data->end_prog_sem = malloc(sizeof(t_named_semaphores));
	if (!data->end_prog_sem)
		return (free(data->die_sem), free(data->global_sem),
			free(data->forks_sem), -1);
	data->pids = malloc(sizeof(int) * data->philo_nbr);
	if (!data->pids)
		return (free(data->die_sem), free(data->global_sem),
			free(data->forks_sem), -1);
	data->die_sem->sem = NULL;
	data->global_sem->sem = NULL;
	data->forks_sem->sem = NULL;
	data->end_prog_sem->sem = NULL;
	data->die_sem->name = NULL;
	data->global_sem->name = NULL;
	data->forks_sem->name = NULL;
	data->end_prog_sem->name = NULL;
	return (0);
}

static int sem_forks(t_named_semaphores **sem, char *namee, int philo_nbr)
{
	char *name;

	name = ft_strjoin(namee, NULL);
	(*sem)->name = name;
	sem_unlink(name);
	(*sem)->sem = sem_open(name, O_CREAT | O_EXCL, 0644, philo_nbr);
	// free(name);
	if ((*sem)->sem == SEM_FAILED)
	{
		printf("Failed to create semaphore\n");
		// (*sem)->sem = NULL;
		return (-1);
	}
	return (0);
}

static int ft_sem_open(t_named_semaphores **sem, char *namee, int id)
{
	char *name;
	char *id_str;

	id_str = ft_itoa(id);
	name = ft_strjoin(namee, id_str);
	free(id_str);
	(*sem)->name = name;
	sem_unlink(name);
	(*sem)->sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if ((*sem)->sem == SEM_FAILED)
	{
		printf("Failed to create semaphore %s\n", name);
		return (-1);
	}
	return (0);
}

int	init_data(t_program *data)
{
	if(program_sem_init(data))
		exit_when_error("Error in sem_init !\n");
	memset(&data->philos, 0, sizeof(t_philo));
	data->philos.program = data;
	if(sem_forks(&data->forks_sem, "forks_sem", data->philo_nbr))
	{
		printf("sem_open faild\n");
		clean_up(data, 1, 1);
		return (-1);
	}
	if(ft_sem_open(&data->die_sem, "die_sem", -1))
	{
		printf("sem_open faild\n");
		clean_up(data, 1, 1);
		return (-1);
	}
	if(ft_sem_open(&data->global_sem, "global_sem", -1))
	{
		printf("sem_open faild\n");
		clean_up(data, 1, 1);
		return (-1);
	}
	if(ft_sem_open(&data->end_prog_sem, "end_prog_sem", -1))
	{
		printf("sem_open faild\n");
		clean_up(data, 1, 1);
		return (-1);
	}
	return (0);
}

int open_sems(t_philo *philo)
{
	philo->local_sem = malloc(sizeof(t_named_semaphores));
	philo->meal_sem = malloc(sizeof(t_named_semaphores));
	philo->value_sem = malloc(sizeof(t_named_semaphores));
	if(ft_sem_open(&philo->local_sem, "local", philo->id))
		return (-1);
	if(ft_sem_open(&philo->meal_sem, "meal", philo->id))
		return (-1);
	if(ft_sem_open(&philo->value_sem, "value", philo->id))
		return (-1);
	return (0);
}