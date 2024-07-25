/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:34 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/25 11:03:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_program t_program;

typedef struct s_fork
{
    t_mtx fork;
    int     fork_id;
}       t_fork;

typedef struct s_philo
{
    int         id;
    pthread_t   thread_id;
    long        meals_eaten;
    long        last_eating_time;
	bool        is_full;
	t_fork      *right_fork;
	t_fork      *left_fork;
    t_program   *program;
    
}   t_philo;


struct s_program
{
    long    num_of_philos;
    long        time_to_eat;
    long        time_to_sleep;
    long        time_to_die;
    long        num_of_meals;
    long        start_of_program;
    long        end_of_program;
    int			dead_flag;
    t_fork      *forks;
	t_philo		*philos;
};


int     ft_isdigit(int c);
int     is_space(int c);
long    ft_atol(char *str);
void    exit_when_error(char* str);
void check_args(t_program *data, char **av, int ac);
#endif