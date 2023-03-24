/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:31:11 by aurel             #+#    #+#             */
/*   Updated: 2023/03/24 10:56:33 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	print(t_philo *philo, t_state	state)
{
	pthread_mutex_lock(&philo->parent_call->print);
	check_death(philo);
	if (state == EATING)
	{
		philo->last_eat = timer();
		philo->eat_count++;
	}
	if (philo->state != DEAD)
		printf("%llu %d %s\n", timer(), philo->philo_nbr + 1, state_msg(state));
	pthread_mutex_unlock(&philo->parent_call->print);
}

void	routine(t_philo *philo)
{
	while ((philo->eat_count != philo->parent_call->must_eat) && \
														philo->state != DEAD)
	{
		if (philo->state == THINKING)
		{
			thinking(philo);
			if (philo->parent_call->philo_are_even == FALSE \
									&& philo->philo_nbr % 2 == 0)
				ft_usleep(30);
		}
		if (philo->state == WAITING)
			take_fork(philo);
		if (philo->state == EATING)
			eating(philo);
		if (philo->state == SLEEPING)
			sleeping(philo);
	}
}

void	check_while_waiting_fork(t_parent *parent, t_philo *philo)
{
	int		i;
	int		count;

	count = 0;
	while (TRUE)
	{
		i = -1;
		while (++i < parent->number_of_philo)
		{
			pthread_mutex_lock(&parent->print);
			if (timer() - philo[i].last_eat >= time_to_die(philo))
			{
				if (check_if_satisfied_or_dead(parent, philo, &count, \
																&i) == FALSE)
					continue ;
				else
					return ;
			}
			pthread_mutex_unlock(&parent->print);
		}
		ft_usleep(5);
	}
}

int	main(int argc, char **argv)
{
	t_parent	parent;
	t_philo		*philo;

	check_invalid_args(argc, argv);
	ft_bzero(&parent, sizeof(t_parent));
	parent.number_of_philo = ft_atoi(argv[1]);
	philo_spawn(&philo, &parent);
	parent_init(&parent, philo, argv, argc);
	philo_init(&parent, philo);
	init_mutex(&parent);
	init_threads(&parent, philo);
	check_while_waiting_fork(&parent, philo);
	wait_threads(&parent);
	destroy_threads(&parent);
	exit_philo(&parent, &philo, NULL);
}
