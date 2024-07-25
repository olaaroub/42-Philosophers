/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:11:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/25 15:15:19 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


static void    give_forks(t_philo *philo, t_fork *forks, int philo_position)
{
    long nbr_philos;
    
    nbr_philos = philo->program->num_of_philos;
    philo->left_fork = &forks[philo_position + 1 % nbr_philos];
    philo->right_fork = &forks[philo_position];
    if(philo->id % 2 == 0)
    {
        philo->right_fork = &forks[philo_position];
        philo->left_fork = &forks[philo_position + 1 % nbr_philos];
    }
}

static void    init_philo(t_program *data)
{
    int i;
    t_philo *philo;

    i = -1;
    while(++i < data->num_of_philos)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->is_full = 0;
        philo->meals_eaten = 0;
        philo->program = data;
        give_forks(philo, data->forks, i);
    }
}

void    init_data(t_program *data)
{
    int i;
    
    i = -1;
    data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
    if(!data->philos)
        exit_when_error("Malloc error !\n");
    data->forks = malloc(sizeof(t_fork) * data->num_of_philos);
    if(!data->forks)
        exit_when_error("Malloc error !\n");
    while(++i < data->num_of_philos)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL); 
        data->forks->fork_id = i++;
    }
    init_philo(data);
}
