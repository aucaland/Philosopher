/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:19:07 by aucaland          #+#    #+#             */
/*   Updated: 2023/03/13 13:19:07 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	fork_repartion_even_nbr_philo(t_philo *philo, int behavior)
{
	if (behavior == FIRST_LOCK)
	{
		if (philo->odd == FALSE)
			pthread_mutex_lock(&philo->parent_call->fork[philo->rfork]);
		else
			pthread_mutex_lock(&philo->parent_call->fork[philo->own_fork]);
	}
	else if (behavior == SECOND_LOCK)
	{
		if (philo->odd == FALSE)
			pthread_mutex_lock(&philo->parent_call->fork[philo->own_fork]);
		else
			pthread_mutex_lock(&philo->parent_call->fork[philo->lfork]);
	}
}

void	fork_repartition(t_philo *philo, int behavior)
{
	if (behavior == FIRST_LOCK)
		fork_repartion_even_nbr_philo(philo, FIRST_LOCK);
	else if (behavior == SECOND_LOCK)
		fork_repartion_even_nbr_philo(philo, SECOND_LOCK);
}

t_bool	drop_the_fork(t_philo *philo)
{
	if (philo->state == DEAD)
	{
		if (philo->odd == FALSE)
			unlock(RIGHT_FORK, philo->parent_call, philo, philo->odd);
		else
			unlock(OWN_FORK, philo->parent_call, philo, philo->odd);
		return (TRUE);
	}
	return (FALSE);
}
