/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:39:32 by aucaland          #+#    #+#             */
/*   Updated: 2023/03/14 19:22:34 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

unsigned long long int	timer(void)
{
	struct timeval				tv;
	static unsigned long long	start;
	unsigned long long			time;

	time = 0;
	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		time = 0;
	}
	else
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start;
	return (time);
}

char	*state_msg(t_state state)
{
	if (state == EATING)
		return (EATING_MSG);
	else if (state == SLEEPING)
		return (SLEEPING_MSG);
	else if (state == THINKING)
		return (THINKING_MSG);
	else if (state == TAKING || state == WAITING)
		return (TAKING_FORK_MSG);
	else if (state == DEAD)
		return (DYING_MSG);
	return (NULL);
}

void	ft_usleep(unsigned long long int time)
{
	unsigned long long	until;

	if (time == 0)
	{
		usleep(10);
		return ;
	}
	until = timer() + time;
	while (timer() < until)
		usleep(50);
}
