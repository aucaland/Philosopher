/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:31:11 by aurel             #+#    #+#             */
/*   Updated: 2023/02/28 15:00:12 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

unsigned long long timer() {
	struct timeval tv;
	static unsigned long long	start;
	unsigned long long time = 0;
	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		time = start;
	}
	else
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start;
	return time;
}

t_error	philo_spawn(t_parent *parent)
{
	parent->philo = ft_calloc(parent->number_of_philo, sizeof(t_philo));
	if (!parent->philo)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

void	philo_init(t_parent *parent)
{
	int	i;

	i = -1;
	while (++i < parent->number_of_philo)
	{
		parent->philo[i].own_fork = i;
		if (i == parent->number_of_philo - 1)
			parent->philo[i].lfork = 0;
		else
			parent->philo[i].lfork = i + 1;
		parent->philo[i].is_alive = FALSE;
		parent->philo[i].is_eating = FALSE;
		parent->philo[i].is_sleeping = FALSE;
		parent->philo[i].philo_nbr = i;
	}
}

int main(int argc, char **argv)
{
	t_parent	parent;

	if (argc < 5 || argc > 6) //TODO: create a check function for each arg
		exit_philo(NULL, NBR_ARGUMENTS);
	check_invalid_args(argc, argv);
	ft_bzero(&parent, sizeof(t_parent));
	parent.number_of_philo = ft_atoi(argv[1]);
	if (philo_spawn(&parent) == MALLOC_ERROR)
		exit_philo(&parent, FAILED_ALLOC);
	philo_init(&parent);




}