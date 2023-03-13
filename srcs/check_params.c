/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucaland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:43:55 by aurel             #+#    #+#             */
/*   Updated: 2023/03/13 11:16:11 by aucaland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

t_bool	is_valid_digit(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && (argv[i][j] != '+'))
				return (FALSE);
			++j;
		}
		++i;
	}
	return (TRUE);
}

t_bool	valid_philo_number(int philo_number)
{
	if (philo_number < 1)
		return (FALSE);
	return (TRUE);
}

void	check_invalid_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		exit_philo(NULL, NULL, NBR_ARGUMENTS);
	if (is_valid_digit(argv + 1) == FALSE)
		exit_philo(NULL, NULL, INV_DIGIT);
	if (valid_philo_number(ft_atoi(argv[1])) == FALSE)
		exit_philo(NULL, NULL, NEGATIV_PHILO_NBR);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		exit_philo(NULL, NULL, NBR_MEAL);
}
