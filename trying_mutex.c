/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trying_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:38:35 by olaaroub          #+#    #+#             */
/*   Updated: 2024/07/03 12:28:01 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

#define times_to_count 21000

typedef struct  s_mutex
{
    unsigned int count;
    pthread_mutex_t mutex;
}               t_mutex;


void    *handler(void* data)
{
    pthread_t thread;
    t_mutex *mutex;
    unsigned int i;

    thread = pthread_self();
    mutex = (t_mutex*)data;
    
    pthread_mutex_lock(&mutex->mutex);
    printf("Count at the start of thread %ld is %u\n", thread, mutex->count);
    pthread_mutex_unlock(&mutex->mutex);
    
    i = 0;
    while(i < times_to_count)
    {
        pthread_mutex_lock(&mutex->mutex);
        (mutex->count)++;
        pthread_mutex_unlock(&mutex->mutex);
        i++;
    }
    
    pthread_mutex_lock(&mutex->mutex);    
    printf("Count at the end of thread %ld is %u\n", thread, mutex->count);
    pthread_mutex_unlock(&mutex->mutex);
}

int main()
{
    pthread_t t1;
    pthread_t t2;
    t_mutex mutex;
    
    mutex.count = 0;
    printf("Expected count is 42000\n");
    pthread_mutex_init(&mutex.mutex, NULL);
    pthread_create(&t1, NULL, handler, &mutex);
    printf("Created the first thread %ld\n", t1);
    pthread_create(&t2, NULL, handler, &mutex);
    printf("Created the second thread %ld\n", t2);

    pthread_join(t1, NULL);
    printf("Joined the first thread %ld\n", t1);
    pthread_join(t2, NULL);
    printf("Joined the second thread %ld\n", t2);

    if(mutex.count != (2 * times_to_count))
        printf("ERROR: count is %u\n", mutex.count);
    else
        printf("SUCCESS: count is %u\n", mutex.count);
    pthread_mutex_destroy(&mutex.mutex);
}
