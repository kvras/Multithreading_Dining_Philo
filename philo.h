/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:47:50 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/17 05:54:32 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"

typedef struct s_args
{
	int		num_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_eat;
}	t_args;

typedef struct s_philo
{
	t_args			*args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_time_eat_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*meals_lock;
	int				id;
	long			start_time;
	long			last_time_eat;
	int				*num_philo_eat;
}	t_philo;

pthread_mutex_t	*create_mutexes(int nbr_philos);
void			free_philo(t_philo *philo);
void			eating(t_philo *philo, int *meals);
long			get(t_philo *philosophers, int i);
long			get_time(void);
void			ft_sleep(long time_ms);
void			print(char *str, int id, long start_time, \
				pthread_mutex_t *print_lock);
bool			init_vars(t_philo **philosophers, t_args *args, \
				pthread_t **thread_id);
long			ft_atoi(const char *str);
int				get_eat(t_philo philo);
void			assign_vars(t_philo *philo, int i, t_args *args, \
				pthread_mutex_t *forks);
#endif