/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:08:04 by aurel             #+#    #+#             */
/*   Updated: 2023/03/27 15:13:09 by aucaland         ###   ########.fr       */
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
	parent->philo_are_even = TRUE;
	if (parent->number_of_philo % 2 != 0)
		parent->philo_are_even = FALSE;
	parent->time_to_die = ft_atoi(argv[2]);
	parent->time_to_eat = ft_atoi(argv[3]);
	parent->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parent->must_eat = ft_atoi(argv[5]);
	else
		parent->must_eat = -1;
	parent->threads = ft_calloc(parent->number_of_philo, sizeof(pthread_t));
	if (!parent->threads)
		exit_philo(parent, &philo, FAILED_ALLOC);
	parent->fork = ft_calloc(parent->number_of_philo, \
												sizeof(pthread_mutex_t));
	if (!parent->fork)
		exit_philo(parent, &philo, FAILED_ALLOC);
	parent->state = WAITING;
	parent->philo = philo;
}

void	philo_init(t_parent *parent, t_philo *philo)
{
	int	i;

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
		philo[i].odd = FALSE;
		if (i % 2 != 0)
			philo[i].odd = TRUE;
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
	int	i;

	i = -1;
	if (pthread_mutex_init(&parent->print, NULL) == 0)
		exit_philo(parent, NULL, FAILED_MUTEX);
	if (pthread_mutex_init(&parent->state_mutex, NULL) == 0)
		exit_philo(parent, NULL, FAILED_MUTEX);
	while (++i < parent->number_of_philo)
		if (pthread_mutex_init(&parent->fork[i], NULL) == 0)
			exit_philo(parent, NULL, FAILED_MUTEX);
}
