/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:17:28 by aurel             #+#    #+#             */
/*   Updated: 2023/03/13 11:24:53 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	thinking(t_philo *philo)
{
	print(philo, philo->state);
	if (philo->state != DEAD)
		philo->state = WAITING;
}

void	eating(t_philo *philo)
{
	int	odd;

	odd = TRUE;
	if (philo->philo_nbr % 2 == 0)
		odd = FALSE;
	print(philo, philo->state);
	check_death_before_silence(philo, philo->state);
	if (philo->state != DEAD)
	{
		ft_usleep(philo->parent_call->time_to_eat);
		unlock(BOTH_FORKS, philo->parent_call, philo, odd);
		philo->state = SLEEPING;
	}
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

void	fork_repartition_odd_nbr_philo(t_philo *philo, int behavior)
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
	{
		if (philo->parent_call->philo_are_odd == FALSE)
			fork_repartion_even_nbr_philo(philo, FIRST_LOCK);
		else
			fork_repartition_odd_nbr_philo(philo, FIRST_LOCK);
	}
	else if (behavior == SECOND_LOCK)
	{
		if (philo->parent_call->philo_are_odd == FALSE)
			fork_repartion_even_nbr_philo(philo, SECOND_LOCK);
		else
			fork_repartition_odd_nbr_philo(philo, SECOND_LOCK);
	}
}

t_bool	drop_the_fork(t_philo *philo)
{
	if (philo->parent_call->philo_are_odd == FALSE && philo->state == DEAD)
	{
		if (philo->odd == FALSE)
			unlock(RIGHT_FORK, philo->parent_call, philo, philo->odd);
		else
			unlock(OWN_FORK, philo->parent_call, philo, philo->odd);
		return (TRUE);
	}
	else if (philo->parent_call->philo_are_odd == TRUE && philo->state == DEAD)
	{
		if (philo->odd == FALSE)
			unlock(RIGHT_FORK, philo->parent_call, philo, philo->odd);
		else
			unlock(OWN_FORK, philo->parent_call, philo, philo->odd);
		return (TRUE);
	}
	return (FALSE);
}

void	take_fork(t_philo *philo)
{
	if (philo->state == DEAD)
		return ;
	fork_repartition(philo, FIRST_LOCK);
	print(philo, philo->state);
	if (drop_the_fork(philo) == TRUE)
		return ;
	else if (philo->parent_call->number_of_philo == 1)
	{
		philo->state = DEAD;
		drop_the_fork(philo);
		check_death_before_silence(philo, philo->state);
	}
	else
	{
		fork_repartition(philo, SECOND_LOCK);
		print(philo, philo->state);
	}
	if (philo->state == DEAD && philo->parent_call->number_of_philo != 1)
		unlock(BOTH_FORKS, philo->parent_call, philo, philo->odd);
	philo->state = EATING;
}

void	dying(t_philo *philo, unsigned long long int time_to_wait)
{
	ft_usleep(time_to_wait);
	pthread_mutex_lock(&philo->parent_call->state_mutex);
	if (philo->parent_call->state == DEAD)
	{
		pthread_mutex_unlock(&philo->parent_call->state_mutex);
		return ;
	}
	philo->parent_call->state = DEAD;
	pthread_mutex_unlock(&philo->parent_call->state_mutex);
	philo->state = DEAD;
	pthread_mutex_lock(&philo->parent_call->print);
	printf("%llu %d %s\n", timer(), philo->philo_nbr, state_msg(DEAD));
	ft_usleep(time_to_die(philo) + 1);
	pthread_mutex_unlock(&philo->parent_call->print);
}
