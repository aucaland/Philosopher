/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:17:28 by aurel             #+#    #+#             */
/*   Updated: 2023/03/13 12:58:32 by aucaland         ###   ########.fr       */
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
