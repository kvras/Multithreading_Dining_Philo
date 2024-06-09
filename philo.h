/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:47:50 by miguiji           #+#    #+#             */
/*   Updated: 2024/06/09 05:09:02 by miguiji          ###   ########.fr       */
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

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"

typedef struct s_args
{
	int		num_philo;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		num_eat;
}	t_args;

typedef struct s_philo
{
	pthread_mutex_t	*forks;
	t_args			*args;
	int				id;
	long			start_time;
	long			last_time_eat;
	pthread_mutex_t	*lst_time_eat_lock;
	pthread_mutex_t	*print_lock;
}	t_philo;

pthread_mutex_t	*create_mutexes(int nbr_philos);
void			free_philo(t_philo *philo);
void			set(t_philo *philosophers, long time);
long			get(t_philo *philosophers, int i);
long			get_time(void);
void			ft_sleep(long time_ms);
void			print(char *str, int id, long start_time, \
				pthread_mutex_t *print_lock);
bool			init_vars(t_philo **philosophers, t_args *args, \
				pthread_mutex_t **print_lock, pthread_t **thread_id);
#endif