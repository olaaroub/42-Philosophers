/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:01:58 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/28 10:38:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long    read_long(t_mtx *read_mutex, long *value)
{
    long res;
    
    pthread_mutex_lock(read_mutex);
    res = *value;
    pthread_mutex_unlock(read_mutex);
    return res;
}

bool read_bool(t_mtx *read_mutex, bool *value)
{
    bool res;

    pthread_mutex_lock(read_mutex);
    res = *value;
    pthread_mutex_unlock(read_mutex);
    return res;
}

void    set_long(t_mtx *set_mutex, long *variable, long new_val)
{
    pthread_mutex_lock(set_mutex);
    *variable = new_val;
    pthread_mutex_unlock(set_mutex);
}

void    set_bool(t_mtx *set_mutex, bool *variable, bool new_val)
{
    pthread_mutex_lock(set_mutex);
    *variable = new_val;
    pthread_mutex_unlock(set_mutex);
}

bool    end_of_dinner(t_program *data)
{
    bool status;
    status = read_bool(&data->get_mutex, &data->end_of_program);
    return status;
}
