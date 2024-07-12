/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:51:35 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/12 23:35:50 by miguiji          ###   ########.fr       */
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

bool	init_vars(t_philo **philosophers, t_args *args,
			pthread_mutex_t **print_lock, pthread_t **thread_id)
{
	int	i;

	i = 0;
	*philosophers = malloc(sizeof(t_philo) * args->num_philo);
	if (!*philosophers)
		return (false);
	*thread_id = malloc(args->num_philo * sizeof(pthread_t));
	if (!*thread_id)
	{
		free(*philosophers);
		return (false);
	}
	*print_lock = malloc(sizeof(pthread_mutex_t));
	if (!*print_lock)
	{
		free(*philosophers);
		free(*thread_id);
		return (false);
	}
	return (true);
}
