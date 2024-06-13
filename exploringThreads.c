/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exploringThreads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:47:27 by olaaroub          #+#    #+#             */
/*   Updated: 2024/06/13 17:13:28 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

int i = 7;

void* testing2()
{
    printf("I GOT HERE TOO %d \n", i++);
}

void*   testing()
{
    printf("I GOT HERE %d \n", i);
}


int main(void)
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &testing, NULL);
    pthread_create(&thread2, NULL, &testing2, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}
