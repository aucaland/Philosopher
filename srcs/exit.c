/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:13:46 by aucaland          #+#    #+#             */
/*   Updated: 2023/03/02 11:45:50 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	exit_philo(t_parent *parent, t_philo **philo, char *msg)
{
	(void)philo;
	if (parent)
	{
		parent->philo = ft_free(parent->philo);
		parent->fork = ft_free(parent->fork);
		parent->threads = ft_free(parent->threads);
	}
	if (msg)
		printf("%s", msg);
	exit(EXIT_SUCCESS);
}
