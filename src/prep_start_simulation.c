/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_start_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:21:28 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/28 22:53:22 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void think_routine(t_philo *philo)
{
    print_status(philo, THINK);
}

static void    eat_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->first_fork->fork);
    print_status(philo, F_FORK);
    pthread_mutex_lock(&philo->second_fork->fork);
    print_status(philo, S_FORK);
    set_long(&philo->philo_mtx, &philo->last_eating_time, get_current_time());
    philo->meals_eaten++;
    print_status(philo, EAT);
    ft_usleep(philo->program->time_to_eat);
    if(philo->program->num_of_meals > 0 && philo->meals_eaten == philo->program->num_of_meals)
        set_bool(&philo->philo_mtx, &philo->is_full, true);
    pthread_mutex_unlock(&philo->first_fork->fork);
    pthread_mutex_unlock(&philo->second_fork->fork);
}

void   *start_simulation(void *params)
{
    t_philo *philo;

    philo = (t_philo *)params;
    check_threads(philo->program); //waiting for all threads to be created

    while(!end_of_dinner(philo->program))
    {
        if(philo->is_full)
            break;
        eat_routine(philo);
        print_status(philo, SLEEP);
        ft_usleep(philo->program->time_to_sleep);
        think_routine(philo);
    }
    return NULL;
}

void    prepare_simulation(t_program *data)
{
    int i;

    i = -1;
    if(data->num_of_meals == 0)
        return;
    else if(data->philo_nbr == 1)
        return; //todo
    else
    {
         while(++i < data->philo_nbr)
            pthread_create(&data->philos[i].thread_id, NULL, start_simulation, &data->philos[i]);       
    }
    data->start_dinner = get_current_time();
    set_bool(&data->set_mutex, &data->threads_ready, true);
    i = -1;
    while (++i < data->philo_nbr)
        pthread_join(data->philos[i].thread_id, NULL);

}

