/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:15:57 by aucaland          #+#    #+#             */
/*   Updated: 2023/03/13 13:17:31 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	wait_threads(t_parent *parent)
{
	int	i;

	i = 0;
	while (i < parent->number_of_philo)
	{
		pthread_join(parent->threads[i], NULL);
		i++;
	}
}

void	destroy_threads(t_parent *parent)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&parent->print);
	while (i < parent->number_of_philo)
	{
		pthread_mutex_destroy(&parent->fork[i]);
		i++;
	}
}
