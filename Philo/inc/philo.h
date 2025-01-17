/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:34 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/02 20:53:42 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define F_FORK 1
# define S_FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIE 6

typedef pthread_mutex_t		t_mtx;
typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t				thread_id;
	int						id;
	long					meals_eaten;
	long					last_eating_time;
	bool					is_full;
	t_mtx					philo_mtx;
	t_mtx					check_threads_mutex;
	t_mtx					*first_fork;
	t_mtx					*second_fork;
	t_program				*program;

}							t_philo;

struct						s_program
{
	pthread_t				admin_thread;
	bool					threads_ready;
	bool					end_of_program;
	long					all_full;
	long					philo_nbr;
	long					start_dinner;
	long					time_to_eat;
	long					time_to_sleep;
	long					time_to_die;
	long					num_of_meals;
	t_mtx					data_mutex;
	t_mtx					write_mutex;
	t_mtx					*forks;
	t_philo					*philos;
};

long						ft_atol(char *str);
void						exit_when_error(char *str);
void						check_args(t_program *data, char **av, int ac);
void						init_data(t_program *data);
long						read_long(t_mtx *read_mutex, long *value);
bool						read_bool(t_mtx *read_mutex, bool *value);
void						set_bool(t_mtx *data_mutex, bool *variable,
								bool new_val);
void						set_long(t_mtx *data_mutex, long *variable,
								long new_val);
void						prepare_simulation(t_program *data);
void						check_threads(t_program *data);
bool						end_of_dinner(t_program *data);
int							ft_usleep(long milliseconds);
long						get_current_time(void);
void						print_status(t_philo *philo, int id);
void						*admin_routine(void *param);
void						clean_exit(t_program *data);
void						increment(t_mtx *data_mutex, long *variable);
bool						all_philos_full(t_program *data);

#endif