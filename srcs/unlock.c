/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:08:26 by aucaland          #+#    #+#             */
/*   Updated: 2023/03/13 13:11:00 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	unlock_both(t_parent *parent, t_philo *philo, t_bool odd)
{
	if (odd == FALSE)
	{
		pthread_mutex_unlock(&parent->fork[philo->rfork]);
		pthread_mutex_unlock(&parent->fork[philo->own_fork]);
	}
	else
	{
		pthread_mutex_unlock(&parent->fork[philo->lfork]);
		pthread_mutex_unlock(&parent->fork[philo->own_fork]);
	}
}

void	unlock(int which_forks, t_parent *parent, t_philo *philo, t_bool odd)
{
	if (which_forks == LEFT_FORK)
		pthread_mutex_unlock(&parent->fork[philo->lfork]);
	else if (which_forks == RIGHT_FORK)
		pthread_mutex_unlock(&parent->fork[philo->rfork]);
	else if (which_forks == OWN_FORK)
		pthread_mutex_unlock(&parent->fork[philo->own_fork]);
	else if (which_forks == BOTH_FORKS)
		unlock_both(parent, philo, odd);
}
