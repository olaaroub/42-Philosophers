/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:34 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/30 13:10:40 by olaaroub         ###   ########.fr       */
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

typedef struct s_fork
{
	t_mtx					fork;
	int						fork_id;
}							t_fork;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	long					meals_eaten;
	long					last_eating_time;
	bool					is_full;
	t_fork					*first_fork;
	t_fork					*second_fork;
	t_mtx					philo_mtx;
	t_program				*program;

}							t_philo;

struct						s_program
{
	pthread_t				admin_thread;
	long					philo_nbr;
	long					start_dinner;
	bool					threads_ready;
	long					time_to_eat;
	long					time_to_sleep;
	long					time_to_die;
	long					num_of_meals;
	bool					end_of_program;
	t_fork					*forks;
	t_mtx					get_mutex;
	t_mtx					set_mutex;
	t_mtx					write_mutex;
	t_philo					*philos;
};

int							ft_isdigit(int c);
int							is_space(int c);
long						ft_atol(char *str);
void						exit_when_error(char *str);
void						check_args(t_program *data, char **av, int ac);
void						init_data(t_program *data);
long						read_long(t_mtx *read_mutex, long *value);
bool						read_bool(t_mtx *read_mutex, bool *value);
void						set_bool(t_mtx *set_mutex, bool *variable,
								bool new_val);
void						set_long(t_mtx *set_mutex, long *variable,
								long new_val);
void						prepare_simulation(t_program *data);
void						check_threads(t_program *data);
bool						end_of_dinner(t_program *data);
int							ft_usleep(size_t milliseconds);
size_t						get_current_time(void);
void						print_status(t_philo *philo, int id);
void						*admin_routine(void *param);
void						clean_exit(t_program *data);

#endif