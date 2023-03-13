/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:30:53 by aurel             #+#    #+#             */
/*   Updated: 2023/03/13 11:16:50 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

unsigned long long	time_to_eat(t_philo *philo)
{
	return (philo->parent_call->time_to_eat);
}

unsigned long long	time_to_die(t_philo *philo)
{
	return (philo->parent_call->time_to_die);
}

unsigned long long	time_to_sleep(t_philo *philo)
{
	return (philo->parent_call->time_to_sleep);
}
