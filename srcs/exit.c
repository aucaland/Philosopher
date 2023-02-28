/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:13:46 by aucaland          #+#    #+#             */
/*   Updated: 2023/02/28 14:57:15 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	exit_philo(t_parent *parent, char *msg)
{
	if (parent)
	{
		while (parent->philo)
		{
			parent->philo = ft_free(parent->philo);
			parent->philo++;
		}
	}
	if (msg)
		printf("%s", msg);
	exit(EXIT_SUCCESS);
}
