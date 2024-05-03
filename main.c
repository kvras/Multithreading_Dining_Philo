#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


/*GitHub Copilot: `pthread_join` and `pthread_detach` are two functions provided by the POSIX threads library for managing the lifecycle of a thread.

`pthread_join` is used when you want the calling thread (usually the main thread) to wait for a specific thread to finish execution. This is useful 
when you need to ensure that a certain task has been completed before proceeding. For example, if you have a thread that's performing some computation, 
you might want to wait for that computation to finish before using the result in the main thread.

`pthread_detach`, on the other hand, is used when you want to let a thread run independently and have its resources automatically cleaned up when it finishes.
 This is useful when you don't care about the result of the thread, or when you don't need to synchronize your code with the thread's completion. 
 Detached threads are often used for "fire-and-forget" tasks that run in the background.

In terms of benefits:

- `pthread_join` allows for easier synchronization and can be used to retrieve the return value of the thread function.
- `pthread_detach` can save resources as it allows the system to immediately reclaim the thread's resources when it finishes execution.

You should use `pthread_join` when you need to wait for a thread to finish before proceeding, and `pthread_detach` when you want a thread to run independently and clean up automatically.*/

typedef struct
{
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    int nbr_forks;
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_meals;
    
} philo;

pthread_mutex_t *create_mutexes(nbr_philos)
{
    int i;
    pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * nbr_philos);

    i = 0;
    while (i < nbr_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    return forks;
}

void *routine(void *arg)
{
    int id = ((philo *)arg)->id;
    pthread_mutex_t *forks = ((philo *)arg)->forks;
    while(1)
    {
        if(id % 2)
                usleep(10);
        pthread_mutex_lock(&((philo *)arg)->print);
        printf("Philosopher %d is thinking\n", id);
        pthread_mutex_unlock(&((philo *)arg)->print);
        pthread_mutex_lock(&forks[id]);
        if (pthread_mutex_lock(&forks[(id + 1) % ((philo *)arg)->nbr_forks]) != 0)
        {
            pthread_mutex_unlock(&forks[id]);
            continue;
        }
        pthread_mutex_lock(&((philo *)arg)->print);
        printf("Philosopher %d is eating\n", id);
        usleep(200);
        pthread_mutex_unlock(&((philo *)arg)->print);
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % ((philo *)arg)->nbr_forks]);
        pthread_mutex_lock(&((philo *)arg)->print);
        printf("Philosopher %d is sleeping\n", id);
        usleep(200);
        pthread_mutex_unlock(&((philo *)arg)->print);
    }
    return NULL;
}

void create_philos(int nbr)
{
    int i;
    pthread_t philos[nbr];
    philo *philosopher = malloc(sizeof(philo) * nbr);

    i = 0;
    pthread_mutex_t *mutexes = create_mutexes(nbr);
    pthread_mutex_init(&philosopher->print, NULL);
    while (i < nbr)
    {
        philosopher[i].forks = mutexes;
        philosopher[i].nbr_forks = nbr;
        philosopher[i].id = i;
        pthread_create(&philos[i], NULL, routine, &philosopher[i]);
        pthread_detach(philos[i]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    int nbr_philos;
    if (argc != 2)
    {
        printf("Usage: %s <number of philosophers>\n", argv[0]);
        return 1;
    }
    nbr_philos = atoi(argv[1]);
    if (nbr_philos < 2)
    {
        printf("The number of philosophers must be at least 2\n");
        return 1;
    }
    create_philos(nbr_philos);
    while (1);
    return 0;
}