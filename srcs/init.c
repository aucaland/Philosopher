/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:08:04 by aurel             #+#    #+#             */
/*   Updated: 2023/03/07 16:38:34 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	philo_spawn(t_philo	**philo, t_parent *parent)
{
	*philo = ft_calloc(parent->number_of_philo, sizeof(t_philo));
	if (!*philo)
		exit_philo(parent, philo, FAILED_ALLOC);
}

void	parent_init(t_parent *parent, t_philo *philo, char **argv, int argc)
{
	parent->time_to_die = ft_atoi(argv[2]);
	parent->time_to_eat = ft_atoi(argv[3]);
	parent->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parent->must_eat = ft_atoi(argv[5]);
	else
		parent->must_eat = -1;
	parent->threads = ft_calloc(parent->number_of_philo + 1, sizeof(pthread_t));
	if (!parent->threads)
		exit_philo(parent, &philo, FAILED_ALLOC);
	parent->fork = ft_calloc(parent->number_of_philo + 1, sizeof
																(pthread_mutex_t));
	if (!parent->fork)
		exit_philo(parent, &philo, FAILED_ALLOC);
	parent->state = WAITING;
	parent->philo = philo;
}

void	philo_init(t_parent *parent, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < parent->number_of_philo)
	{
		philo[i].own_fork = i;
		if (i == parent->number_of_philo - 1)
			philo[i].lfork = 0;
		else
			philo[i].lfork = i + 1;
		if (i == 0)
			philo[i].rfork = parent->number_of_philo - 1;
		else
			philo[i].rfork = i - 1;
//		dprintf(2, "[%d] == lfork:%d, rfork:%d, ownfork:%d\n",philo[i]
//		.philo_nbr,
//		philo[i]
//		.lfork, philo[i]
//		.rfork, philo[i].own_fork);
		philo[i].state = THINKING;
		philo[i].philo_nbr = i;
		philo[i].last_eat = 0;
		philo[i].eat_count = 0;
		philo[i].parent_call = parent;
	}
}

void	init_threads(t_parent *parent, t_philo *philo)
{
	int	i;

	i = -1;
	timer();
	while (++i < parent->number_of_philo)
		if (pthread_create(&parent->threads[i], NULL, \
		(void *) routine, &philo[i]) != 0)
			exit_philo(parent, &philo, FAILED_THREAD);
}

void	init_mutex(t_parent *parent)
{
	int i;

	i = -1;
	pthread_mutex_init(&parent->print, NULL);
	pthread_mutex_init(&parent->state_mutex, NULL);
	while (++i < parent->number_of_philo)
		pthread_mutex_init(&parent->fork[i], NULL);
}





