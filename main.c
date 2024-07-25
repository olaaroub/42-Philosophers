/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:00:53 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/25 11:16:00 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

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
        pthread_mutex_init(&data->forks[i++].fork, NULL); 
   
}

int main(int ac, char **av)
{
    t_program   data;
    
    if(ac == 6 || ac == 5)
    {
        check_args(&data, av, ac);
        init_data(&data);
        
    }
    else
        exit_when_error("Invalid number of arguments !\n");
    return 0;        
}