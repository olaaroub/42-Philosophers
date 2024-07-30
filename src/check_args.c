/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:14:06 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/28 22:31:01 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	check_numbers(char *av)
{
	int	i;

	if (!*av || !av[0])
		exit_when_error("Invalid arguments !\n");
	i = 0;
	while (is_space(av[i]))
		i++;
	if (av[i] == '+' || av[i] == '-')
	{
		if (av[i] == '-')
			exit_when_error("Arguments should be positive integers !\n");
		i++;
	}
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			exit_when_error("Invalid arguments !\n");
		i++;
	}
	if (ft_atol(av) > INT_MAX)
		exit_when_error("Aguments should be integers !\n");
}

void	check_args(t_program *data, char **av, int ac)
{
	int	arg;

	arg = 1;
	while (arg < ac)
		check_numbers(av[arg++]);
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac > 5)
		data->num_of_meals = ft_atol(av[5]);
	else
		data->num_of_meals = -1;
}
