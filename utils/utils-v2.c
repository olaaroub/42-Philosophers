/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:10:55 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/28 23:08:38 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void    check_threads(t_program *data)
{
    while(!read_bool(&data->get_mutex, &data->threads_ready))
        ;
}

size_t    get_current_time(void)
{
    struct timeval tv;
    
    if(gettimeofday(&tv, NULL) != 0)
        printf("gettimeofday() error \n");
    return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int ft_usleep(size_t time)
{
    size_t start;

    start = get_current_time();
    while((get_current_time() - start) < time)
        usleep(time / 10);
    return 0;
}

void    print_status(t_philo *philo, int state)
{
    long    time_passed;

    time_passed = get_current_time() - philo->program->start_dinner;
    pthread_mutex_lock(&philo->program->write_mutex);
    if(state == F_FORK)
        printf("%-6ld %d has taken first fork\n", time_passed, philo->id);
    if(state == S_FORK)
        printf("%-6ld %d has taken second fork\n", time_passed, philo->id);
    if(state == EAT)
        printf("%-6ld %d is eating\n", time_passed, philo->id);
    if(state == SLEEP)
        printf("%-6ld %d is sleeping\n", time_passed, philo->id);
    if(state == THINK)
        printf("%-6ld %d is thinking\n", time_passed, philo->id);
    if(state == DIE)
        printf("%-6ld %d died\n", time_passed, philo->id);
    pthread_mutex_unlock(&philo->program->write_mutex);
}
