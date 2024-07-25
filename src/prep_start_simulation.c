/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_start_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:21:28 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/25 18:16:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    prepare_simulation(t_program *data)
{
    int i;

    i = -1;
    if(data->num_of_meals == 0)
        return;
    else if(data->num_of_philos == 1)
        return; //todo
    else
    {
         while(++i < data->num_of_philos)
            pthread_create(&data->philos[i].id, NULL, start_simulation, data->philos);       
    }
    set_bool(&data->set_mutex, data->threads_state, true);
    
}

void    start_simulation(void *params)
{
    t_philo *data;

    data = (t_philo *)params;
    init_all_threads(data->program);
    
    
}
