/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:10:23 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/05 12:14:57 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>

void *routine(void *v)
{
    printf("Hello word");
}

int main()
{
    pthread_t t1;

    pthread_create(&t1, NULL, &routine, NULL);
}