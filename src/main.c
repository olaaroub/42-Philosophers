/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:00:53 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/30 13:34:58 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_program	data;

	if (ac == 6 || ac == 5)
	{
		check_args(&data, av, ac);
		init_data(&data);
		prepare_simulation(&data);
		clean_exit(&data);
	}
	else
		exit_when_error("Invalid number of arguments !\n");
	return (0);
}
