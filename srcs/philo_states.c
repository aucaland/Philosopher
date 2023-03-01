/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:17:28 by aurel             #+#    #+#             */
/*   Updated: 2023/03/01 17:05:35 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	thinking(t_philo *philo)
{
	print(philo, philo->state);
	if (philo->state != DEAD)
		philo->state = EATING;
}

void	eating(t_philo *philo)
{
	print(philo, philo->state);
	check_death_before_silence(philo, philo->state);
	if (philo->state != DEAD)
	{
		ft_usleep(philo->parent_call->time_to_sleep);
		philo->state = SLEEPING;
	}
	unlock(BOTH_FORKS, philo->parent_call, philo);
}

void	sleeping(t_philo *philo)
{
	print(philo, philo->state);
	check_death_before_silence(philo, philo->state);
	if (philo->state != DEAD)
	{
		ft_usleep(philo->parent_call->time_to_sleep);
		philo->state = THINKING;
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->state == DEAD)
		return ;
	pthread_mutex_lock(&philo->parent_call->fork[philo->own_fork]);
	print(philo, philo->state);
	if (philo->state == DEAD)
		unlock(OWN_FORK, philo->parent_call, philo);
	else if (philo->parent_call->number_of_philo <= 1)
	{
		philo->state = DEAD;
		unlock(OWN_FORK, philo->parent_call, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->parent_call->fork[philo->lfork]);
		print(philo, philo->state);
	}
	if (philo->state == DEAD)
		unlock(BOTH_FORKS, philo->parent_call, philo);
}