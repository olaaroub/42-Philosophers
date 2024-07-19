/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:14:06 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/19 12:02:02 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

static unsigned long ft_atol(char *str)
{
    unsigned long	res;
	int		    i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > LONG_MAX)
			return (res);
	}
	return (res);
}

static void    check_digits(char *av)
{
	int	i;

	if (!*av || !av[0])
		exit_when_error("Invalid arguments !\n");
    i = 0;
    while (av[i])
    {
        if (!ft_isdigit(av[i]))
            exit_when_error("Invalid arguments !\n");
        i++;
    }
}

void check_args(char **av, int ac)
{
    int arg;
    arg = 1;
    while(arg < ac)
    {
        check_digits(av[arg]);
        arg++;
    }
    if(ft_atol(av[2]) > LONG_MAX)
        exit_when_error("Invalid arguments !\n");
    if(ft_atol(av[3]) > LONG_MAX)
        exit_when_error("Invalid arguments !\n");
    if(ft_atol(av[4]) > LONG_MAX )
        exit_when_error("Invalid arguments !\n");
    if(ft_atol(av[1]) > 200 || ft_atol(av[1]) <= 0)
        exit_when_error("Invalid arguments !\n");
    if(ft_atol(av[5]) < 1)
        exit_when_error("Invalid arguments !\n");
}
