/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:43:55 by aurel             #+#    #+#             */
/*   Updated: 2023/02/28 15:03:36 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	check_invalid_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1)
		exit_philo(NULL, NBR_PHILOS);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		exit_philo(NULL, NBR_MEAL);
}