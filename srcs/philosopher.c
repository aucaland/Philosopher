/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:31:11 by aurel             #+#    #+#             */
/*   Updated: 2023/02/27 14:13:43 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

t_error	philo_spawn(t_parent *parent, int nbr_of_philo)
{
	parent->philo = ft_calloc(nbr_of_philo, sizeof(t_philo));
	if (!parent->philo)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_parent	parent;

	if (argc < 5 && argc > 6)
		return (printf("%s", INV_ARGUMENTS));

	ft_bzero(&parent, sizeof(t_parent));
	if (philo_spawn(&parent) == MALLOC_ERROR)
		exit_malloc(&parent);


}