/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:44 by aucaland          #+#    #+#             */
/*   Updated: 2023/03/13 13:51:47 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	check_death_before_silence(t_philo *philo, t_state state)
{
	unsigned long long	time_to_wait;
	unsigned long long	time_without_eat;

	if (state == EATING)
	{
		time_without_eat = timer() - philo->last_eat + time_to_eat(philo);
		time_to_wait = time_to_die(philo) - (timer() - philo->last_eat);
		if (time_without_eat > time_to_die(philo))
			dying(philo, time_to_wait);
	}
	else if (state == SLEEPING)
	{
		time_without_eat = timer() - philo->last_eat + time_to_sleep(philo);
		time_to_wait = time_to_die(philo) - (timer() - philo->last_eat);
		if (time_without_eat > time_to_die(philo))
			dying(philo, time_to_wait);
	}
	else if (philo->state == DEAD && philo->parent_call->number_of_philo == 1)
		dying(philo, philo->parent_call->time_to_die);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->parent_call->state_mutex);
	if (philo->parent_call->state == DEAD)
	{
		philo->state = philo->parent_call->state;
		pthread_mutex_unlock(&philo->parent_call->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->parent_call->state_mutex);
	if (timer() - philo->last_eat >= time_to_die(philo) && \
	philo->parent_call->state != DEAD)
	{
		philo->parent_call->state = DEAD;
		philo->state = DEAD;
		printf("%llu %d %s\n", timer(), philo->philo_nbr, state_msg(DEAD));
	}
}

t_bool	check_if_satisfied_or_dead(t_parent *parent, t_philo *philo, int
*count, int *i)
{
	if (parent->state == DEAD || \
										parent->must_eat == philo[*i].eat_count)
	{
		if (parent->must_eat == philo[*i].eat_count)
			(*count)++;
		if ((*count) != parent->number_of_philo && parent->must_eat != -1)
		{
			pthread_mutex_unlock(&parent->print);
			return (FALSE);
		}
		pthread_mutex_unlock(&parent->print);
		return (TRUE);
	}
	parent->state = DEAD;
	printf("%llu %d %s\n", timer(), philo[*i].philo_nbr, \
														state_msg(DEAD));
	pthread_mutex_unlock(&parent->print);
	return (TRUE);
}
