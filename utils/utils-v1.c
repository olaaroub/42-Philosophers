/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:42:22 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/19 15:14:17 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void    exit_when_error(char* str)
{
    printf("%s", str);
    exit(EXIT_FAILURE);
}
