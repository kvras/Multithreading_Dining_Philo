/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:56:53 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/17 00:31:31 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				meals;

	meals = 0;
	philo = arg;
	forks = philo->forks;
	print("is thinking", philo->id + 1, philo->start_time, philo->print_lock);
	if (philo->id % 2)
		ft_sleep(philo->args->time_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&forks[philo->id]);
		print(FORK, philo->id + 1, (philo)->start_time, philo->print_lock);
		pthread_mutex_lock(&forks[(philo->id + 1) % philo->args->num_philo]);
		print(FORK, philo->id + 1, (philo)->start_time, philo->print_lock);
		print(EAT, philo->id + 1, (philo)->start_time, philo->print_lock);
		eating(philo, &meals);
		pthread_mutex_unlock(&forks[philo->id]);
		pthread_mutex_unlock(&forks[(philo->id + 1) % philo->args->num_philo]);
		print(SLEEP, philo->id + 1, (philo)->start_time, philo->print_lock);
		ft_sleep(philo->args->time_sleep);
		print(THINK, philo->id + 1, (philo)->start_time, philo->print_lock);
	}
	return (NULL);
}

void	is_died(t_philo *philo, pthread_t *thread_id, int i, long time)
{
	long	start_time;

	while (1)
	{
		i = 0;
		while (i < philo->args->num_philo)
		{
			start_time = philo[i].start_time;
			time = get_time();
			if (time - get(philo, i) >= philo[i].args->time_die || \
				get_eat(philo[i]) == philo[i].args->num_philo)
			{
				if (time - get(philo, i) >= philo[i].args->time_die)
					print("died", i + 1, start_time, philo[i].print_lock);
				else
					pthread_mutex_lock(philo[i].print_lock);
				ft_sleep(philo[i].args->time_sleep + philo[i].args->time_eat);
				free(thread_id);
				free_philo(philo);
				return ;
			}
			i++;
			usleep(1000);
		}
	}
}

void	philosophers(pthread_mutex_t *forks, t_args *args, int i)
{
	t_philo			*philosophers;
	pthread_t		*thread_id;
	int				*var;

	var = malloc(sizeof(int));
	if (!var)
		return ;
	*var = 0;
	if (!init_vars(&philosophers, args, &thread_id))
		return ;
	while (++i < args->num_philo)
	{
		assign_vars(philosophers, i, args, forks);
		philosophers[i].num_philo_eat = var;
		philosophers[i].last_time_eat_lock = malloc(sizeof(pthread_mutex_t));
		if (!philosophers[i].last_time_eat_lock)
			return ;
		philosophers[i].print_lock = philosophers->print_lock;
		philosophers[i].meals_lock = philosophers->meals_lock;
		pthread_mutex_init(philosophers[i].last_time_eat_lock, NULL);
		pthread_create(&thread_id[i], NULL, routine, &philosophers[i]);
		pthread_detach(thread_id[i]);
	}
	is_died(philosophers, thread_id, 0, 0);
}

t_args	*is_valid_args(int argc, char *argv[])
{
	t_args	*args;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), NULL);
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->num_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	if (args->num_philo < 1 || args->time_die < 0 || args->time_eat < 0 || \
		args->time_sleep < 0)
		return (printf("Error: Wrong arguments\n"), free(args), NULL);
	if (argc == 6)
	{
		args->num_eat = ft_atoi(argv[5]);
		if (args->num_eat < 1)
			return (printf("Error: Wrong arguments\n"), free(args), NULL);
	}
	else
		args->num_eat = -1;
	return (args);
}

int	main(int argc, char *argv[])
{
	t_args			*args;
	pthread_mutex_t	*forks;

	args = is_valid_args(argc, argv);
	if (!args)
		return (0);
	forks = create_mutexes(args->num_philo);
	if (!forks)
		return (0);
	philosophers(forks, args, -1);
	return (0);
}
