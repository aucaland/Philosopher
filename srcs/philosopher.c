/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:31:11 by aurel             #+#    #+#             */
/*   Updated: 2023/03/01 14:36:20 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"
# include <pthread.h>

unsigned long long timer() {
	struct timeval tv;
	static unsigned long long	start;
	unsigned long long time = 0;
	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		time = 0;
	}
	else
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start;
	return time;
}

void	philo_spawn(t_philo	**philo)
{
	*philo = ft_calloc(parent->number_of_philo, sizeof(t_philo));
	if (!*philo)
		exit_philo(parent, FAILED_ALLOC);
}

void	parent_init(t_parent *parent, t_philo *philo, char **argv, int argc)
{
	parent->number_of_philo = ft_atoi(argv[1]);
	parent->time_to_die = ft_atoi(argv[2]);
	parent->time_to_eat = ft_atoi(argv[3]);
	parent->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parent->meals_min = ft_atoi(argv[5]);
	parent->threads = ft_calloc(parent->number_of_philo, sizeof(pthread_t));
	if (!parent->threads)
		exit_philo(parent, FAILED_ALLOC);
	parent->fork = ft_calloc(parent->number_of_philo, sizeof(pthread_mutex_t));
	if (!parent->fork)
		exit_philo(parent, FAILED_ALLOC);
	parent->philo = philo;
}

void	philo_init(t_parent *parent, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < parent->number_of_philo)
	{
		(*philo)[i].own_fork = i;
		if (i == parent->number_of_philo - 1)
			(*philo)[i].lfork = 0;
		else
			(*philo)[i].lfork = i + 1;
		(*philo)[i].state = WAITING;
		(*philo)[i].philo_nbr = i;
		(*philo)[i].last_eat = 0;
		(*philo)[i].eat_count = 0;
		(*philo)[i].parent_call = parent;
	}
}

char	*state_msg(t_state state)
{
	if (state == EATING)
		return (EATING_MSG);
	else if (state == SLEEPING)
		return (SLEEPING_MSG);
	else if (state == THINKING)
		return (DYING_MSG);
	else if (state == TAKING)
		return (TAKING_FORK_MSG);
}

t_state	print(t_philo *philo, t_state	state)
{
	pthread_mutex_lock(philo->parent_call->print);
	philo->state = philo->parent_call->state;
	if (state == EATING)
	{
		philo->last_eat = timer();
		philo->eat_count++;
	}
	if (philo->state != DEAD)
		printf("%llu %d %s", timer(), philo->philo_nbr, state_msg(state));

}

void	routine(t_philo *philo)
{

}

void	unlock(int which_forks, t_parent *parent, t_philo *philo)
{
	if (which_forks == LEFT_FORK)
		pthread_mutex_unlock(parent->fork[philo->lfork]);
	else if (which_forks == OWN_FORK)
		pthread_mutex_unlock(parent->fork[philo->own_fork]);
	else if (which_forks == BOTH_FORKS)
	{
		pthread_mutex_unlock(parent->fork[philo->lfork]);
		pthread_mutex_unlock(parent->fork[philo->own_fork]);
	}
}

void	init_threads(t_parent *parent)
{
	int	i;

	i = -1;
	timer();
	while (++i < parent->number_of_philo)
	if (pthread_create(&parent->threads[i], NULL, \
		(void *) routine, &parent->philo[i]) != 0)
		exit_philo(parent, FAILED_THREAD);
}

void	init_mutex(t_parent *parent)
{
	int i;

	i = -1;
	pthread_mutex_init(parent->print, NULL);
	while (++i < parent->number_of_philo)
		pthread_mutex_init(parent->fork[i], NULL);

}

int main(int argc, char **argv)
{
	t_parent	parent;
	t_philo		*philo;

	if (argc < 5 || argc > 6) //TODO: create a check function for each arg
		exit_philo(NULL, NBR_ARGUMENTS);
	check_invalid_args(argc, argv);
	ft_bzero(&parent, sizeof(t_parent));
	philo_spawn(&philo);
	philo_init(&parent, &philo);
	parent_init(&parent, philo, argv, argc);
	init_mutex(&parent);
	init_threads(&parent);

}