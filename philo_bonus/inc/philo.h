/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:01:34 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/16 16:15:01 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define F_FORK 1
# define S_FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIE 6

typedef struct s_program	t_program;

typedef struct s_named_semaphores
{
	sem_t					*sem;
	char					*name;
}							t_named_semaphores;

typedef struct s_wait
{
	sem_t				*stop;
	sem_t				*died;
	int					*pids;
	long				pids_num;
	bool				stop_flag;
}						t_wait;


typedef struct s_philo
{
	pthread_t				thread;
	t_named_semaphores		*local_sem;
	t_named_semaphores		*meal_sem;
	t_named_semaphores		*value_sem;
	// long					start;
	bool					is_full;
	int						id;
	long					meals_eaten;
	long					last_eating_time;
	t_program				*program;
}							t_philo;


struct						s_program
{
	t_named_semaphores		*die_sem;
	t_named_semaphores		*global_sem;
	t_named_semaphores		*forks_sem;
	t_named_semaphores		*end_prog_sem;
	bool					end_of_program;
	int 					*pids;
	long					philo_nbr;
	long					start_dinner;
	long					time_to_eat;
	long					time_to_sleep;
	long					time_to_die;
	long					num_of_meals;
	t_philo					philos;
};

int							ft_isdigit(int c);
int							is_space(int c);
long						ft_atol(char *str);
void						exit_when_error(char *str);
void						check_args(t_program *data, char **av, int ac);
int						init_data(t_program *data);
long						read_long(sem_t *sem, long *value);
bool						read_bool(sem_t *sem, bool *value);
void						set_bool(sem_t *sem, bool *variable,
								bool new_val);
void						set_long(sem_t *sem, long *variable,
								long new_val);
void						prepare_simulation(t_program *data);
bool						end_of_dinner(t_program *data);
int							ft_usleep(long milliseconds);
long						get_current_time(void);
void						print_status(t_philo *philo, int id);
void						*admin_routine(void *param);
void	clean_up(t_program *data, unsigned int exit_num, bool mode);
int open_sems(t_philo *philo);
long check_death(sem_t *from, sem_t *lock);

#endif