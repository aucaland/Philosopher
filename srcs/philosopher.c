/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:31:11 by aurel             #+#    #+#             */
/*   Updated: 2023/02/28 15:50:58 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

unsigned long long timer() {
	struct timeval tv;
	static unsigned long long	start;
	unsigned long long time = 0;
	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		time = start;
	}
	else
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start;
	return time;
}

t_error	philo_spawn(t_parent *parent)
{
	parent->philo = ft_calloc(parent->number_of_philo, sizeof(t_philo));
	if (!parent->philo)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

t_error	parent_init(t_parent *parent, char **argv, int argc)
{
	parent->number_of_philo = ft_atoi(argv[1]);
	parent->time_to_die = ft_atoi(argv[2]);
	parent->time_to_eat = ft_atoi(argv[3]);
	parent->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parent->meals_min = ft_atoi(argv[5]);
	parent->fork = ft_calloc(parent->number_of_philo, sizeof(pthread_mutex_t));
	if (!parent->fork)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

void	philo_init(t_parent *parent)
{
	int	i;

	i = -1;
	while (++i < parent->number_of_philo)
	{
		parent->philo[i].own_fork = i;
		if (i == parent->number_of_philo - 1)
			parent->philo[i].lfork = 0;
		else
			parent->philo[i].lfork = i + 1;
		parent->philo[i].is_alive = FALSE;
		parent->philo[i].is_eating = FALSE;
		parent->philo[i].is_sleeping = FALSE;
		parent->philo[i].philo_nbr = i;
	}
}

t_error	init_threads(t_parent *parent)
{
	(void)parent;
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_parent	parent;

	if (argc < 5 || argc > 6) //TODO: create a check function for each arg
		exit_philo(NULL, NBR_ARGUMENTS);
	check_invalid_args(argc, argv);
	ft_bzero(&parent, sizeof(t_parent));
	if (parent_init(&parent, argv, argc) == MALLOC_ERROR)
		exit_philo(&parent, FAILED_ALLOC);
	if (philo_spawn(&parent) == MALLOC_ERROR)
		exit_philo(&parent, FAILED_ALLOC);
	philo_init(&parent);
	init_threads(&parent);




}