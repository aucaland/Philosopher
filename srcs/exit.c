/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:13:46 by aucaland          #+#    #+#             */
/*   Updated: 2023/02/27 14:13:46 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	exit_malloc(t_parent *parent)
{
	if (parent)
	{
		while (parent->philo)
		{
			parent->philo = ft_free(parent->philo);
			parent->philo++;
		}
	}
	exit(EXIT_SUCCESS);
}
