/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:46:15 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/13 00:03:21 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->num_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		pthread_mutex_destroy(philo[i].last_time_eat_lock);
		pthread_mutex_destroy(philo[i].print_lock);
		free(philo[i].last_time_eat_lock);
		i++;
	}
	free(philo->args);
	free(philo->forks);
	free(philo->print_lock);
	free(philo);
}

void	set(t_philo *philosophers, long time)
{
	pthread_mutex_lock(philosophers->last_time_eat_lock);
	philosophers->last_time_eat = time;
	pthread_mutex_unlock(philosophers->last_time_eat_lock);
}

long	get(t_philo *philosophers, int i)
{
	long	time;

	pthread_mutex_lock(philosophers[i].last_time_eat_lock);
	time = philosophers[i].last_time_eat;
	pthread_mutex_unlock(philosophers[i].last_time_eat_lock);
	return (time);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long time_ms)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_ms)
		usleep(500);
}
