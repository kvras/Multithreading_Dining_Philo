/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:51:35 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/17 01:47:17 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, int id, long start_time, pthread_mutex_t *print_lock)
{
	pthread_mutex_lock(print_lock);
	printf("%ld %d %s\n", get_time() - start_time, id, str);
	if (str[0] != 'd')
		pthread_mutex_unlock(print_lock);
}

pthread_mutex_t	*create_mutexes(int nbr_philos)
{
	int					i;
	pthread_mutex_t		*forks;

	forks = malloc(sizeof(pthread_mutex_t) * nbr_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nbr_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

bool	init_vars(t_philo **philosophers, t_args *args, pthread_t **thread_id)
{
	*philosophers = malloc(sizeof(t_philo) * args->num_philo);
	if (!*philosophers)
		return (false);
	*thread_id = malloc(args->num_philo * sizeof(pthread_t));
	if (!*thread_id)
		return (free(*philosophers), false);
	(*philosophers)->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!(*philosophers)->print_lock)
	{
		free(*philosophers);
		return (free(*thread_id), false);
	}
	pthread_mutex_init((*philosophers)->print_lock, NULL);
	(*philosophers)->meals_lock = malloc(sizeof(pthread_mutex_t));
	if (!(*philosophers)->meals_lock)
	{
		pthread_mutex_destroy((*philosophers)->print_lock);
		free(*philosophers);
		free(*thread_id);
		return (free((*philosophers)->print_lock), false);
	}
	pthread_mutex_init((*philosophers)->meals_lock, NULL);
	return (true);
}

int	get_eat(t_philo philo)
{
	int	num_eat;

	pthread_mutex_lock(philo.meals_lock);
	num_eat = *philo.num_philo_eat;
	pthread_mutex_unlock(philo.meals_lock);
	return (num_eat);
}

void	assign_vars(t_philo *philo, int i, t_args *args, pthread_mutex_t *forks)
{
	long	time;

	time = get_time();
	philo[i].args = args;
	philo[i].id = i;
	philo[i].start_time = time;
	philo[i].last_time_eat = time;
	philo[i].forks = forks;
}
