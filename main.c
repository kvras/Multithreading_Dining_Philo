/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:56:53 by miguiji           #+#    #+#             */
/*   Updated: 2024/06/09 05:08:03 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	philo = arg;
	forks = philo->forks;
	print("is thinking", philo->id, philo->start_time, philo->print_lock);
	if (philo->id % 2)
		ft_sleep(philo->args->time_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&forks[philo->id]);
		print(FORK, philo->id + 1, (philo)->start_time, philo->print_lock);
		pthread_mutex_lock(&forks[(philo->id + 1) % philo->args->num_philo]);
		print(FORK, philo->id + 1, (philo)->start_time, philo->print_lock);
		print(EAT, philo->id + 1, (philo)->start_time, philo->print_lock);
		set(philo, get_time());
		ft_sleep(philo->args->time_eat);
		pthread_mutex_unlock(&forks[philo->id]);
		pthread_mutex_unlock(&forks[(philo->id + 1) % philo->args->num_philo]);
		print(SLEEP, philo->id + 1, (philo)->start_time, philo->print_lock);
		ft_sleep(philo->args->time_sleep);
		print(THINK, philo->id + 1, (philo)->start_time, philo->print_lock);
	}
	return (NULL);
}

void	is_died(t_philo *philosophers, pthread_t *thread_id)
{
	int		i;
	long	time;
	long	start_time;

	while (1)
	{
		i = 0;
		while (i < philosophers->args->num_philo)
		{
			start_time = philosophers[i].start_time;
			time = get_time();
			if (time - get(philosophers, i) >= philosophers->args->time_die)
			{
				print("died", i + 1, start_time, philosophers->print_lock);
				sleep(1);
				free(thread_id);
				free_philo(philosophers);
				return ;
			}
			i++;
			usleep(1000);
		}
	}
}

void	philosophers(pthread_mutex_t *forks, t_args *args, long time)
{
	t_philo			*philosophers;
	pthread_mutex_t	*print_lock;
	pthread_t		*thread_id;
	int				i;

	if (!init_vars(&philosophers, args, &print_lock, &thread_id))
		return ;
	pthread_mutex_init(print_lock, NULL);
	i = -1;
	time = get_time();
	while (++i < args->num_philo)
	{
		philosophers[i].forks = forks;
		philosophers[i].args = args;
		philosophers[i].id = i;
		philosophers[i].start_time = time;
		philosophers[i].last_time_eat = philosophers[i].start_time;
		philosophers[i].lst_time_eat_lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philosophers[i].lst_time_eat_lock, NULL);
		philosophers[i].print_lock = print_lock;
		pthread_create(&thread_id[i], NULL, routine, &philosophers[i]);
		pthread_detach(thread_id[i]);
	}
	is_died(philosophers, thread_id);
	return ;
}

t_args	*is_valid_args(int argc, char *argv[])
{
	t_args	*args;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (NULL);
	}
	args = malloc(sizeof(t_args));
	if (!args)
		exit(1);
	args->num_philo = atoi(argv[1]);
	args->time_die = atoi(argv[2]);
	args->time_eat = atoi(argv[3]);
	args->time_sleep = atoi(argv[4]);
	if (argc == 6)
		args->num_eat = atoi(argv[5]);
	else
		args->num_eat = -1;
	return (args);
}

int	main(int argc, char *argv[])
{
	t_args			*args;

	args = is_valid_args(argc, argv);
	if (!args)
		return (0);
	philosophers(create_mutexes(args->num_philo), args, 0);
	return (0);
}
