/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:34 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/19 15:05:34 by olaaroub         ###   ########.fr       */
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


typedef struct s_philo
{
    int id;
    struct s_program   program;
}   t_philo;


typedef struct s_program
{
    t_philo     philo;
}   t_program;


int	    ft_isdigit(int c);
void    exit_when_error(char* str);
void     check_args(char **av, int ac);

#endif