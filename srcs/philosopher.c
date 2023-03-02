/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:31:11 by aurel             #+#    #+#             */
/*   Updated: 2023/03/02 13:42:08 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"


unsigned long long int timer() {
	struct timeval tv;
	static unsigned long long	start;
	unsigned long long time = 0;
	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		time = 0;
	}
	else
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start;
	return time;
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

void	check_death(t_philo *philo)
{
	if (philo->parent_call->state == DEAD)
		philo->state = philo->parent_call->state;
	else
	{
		if (timer() - philo->last_eat >= time_to_die(philo))
		{
			philo->parent_call->state = DEAD;
			philo->state = DEAD;
			printf("%llu %d %s\n", timer(), philo->philo_nbr, state_msg(DEAD));
			ft_usleep(time_to_die(philo));
		}
	}
}

void	print(t_philo *philo, t_state	state)
{
	pthread_mutex_lock(&philo->parent_call->print);
	check_death(philo);
	if (state == EATING)
	{
		philo->last_eat = timer();
		philo->eat_count++;
	}
	if (philo->state != DEAD)
		printf("%llu %d %s\n", timer(), philo->philo_nbr, state_msg(state));
	pthread_mutex_unlock(&philo->parent_call->print);
}

void	check_death_before_silence(t_philo *philo, t_state state)
{
	unsigned long long	time_to_wait;
	unsigned long long	time_without_eat;
	if (state == EATING)
	{
		time_without_eat = timer() - philo->last_eat + time_to_eat(philo);
		time_to_wait = time_without_eat - timer() - philo->last_eat;
		if (time_without_eat > time_to_die(philo))
			dying(philo, time_to_wait);
	}
	else if (state == SLEEPING)
	{
		time_without_eat = timer() - philo->last_eat + time_to_sleep(philo);
		time_to_wait = time_without_eat - timer() - philo->last_eat;
//		dprintf(2, "timer = %llu && without == %llu &&  towait = %llu\n", timer
//		(),time_without_eat,  time_to_wait);
		if (time_without_eat > time_to_die(philo))
			dying(philo, time_to_wait);
	}
	else if (philo->state == DEAD && philo->parent_call->number_of_philo == 1)
		dying(philo, philo->parent_call->time_to_die);
}

void	routine(t_philo *philo)
{
	while ((philo->eat_count != philo->parent_call->must_eat) && philo->parent_call->state !=
			DEAD)
	{
		if (philo->state == THINKING)
		{
			thinking(philo);
			if (philo->philo_nbr % 2 == 0)
				usleep(philo->parent_call->number_of_philo * 100);
		}
		else if (philo->state == WAITING)
			take_fork(philo);
		else if (philo->state == EATING)
			eating(philo);
		else if (philo->state == SLEEPING)
			sleeping(philo);
	}
}

void	unlock(int which_forks, t_parent *parent, t_philo *philo)
{
	if (which_forks == LEFT_FORK)
		pthread_mutex_unlock(&parent->fork[philo->lfork]);
	else if (which_forks == OWN_FORK)
		pthread_mutex_unlock(&parent->fork[philo->own_fork]);
	else if (which_forks == BOTH_FORKS)
	{
		pthread_mutex_unlock(&parent->fork[philo->lfork]);
		pthread_mutex_unlock(&parent->fork[philo->own_fork]);
	}
}



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

int main(int argc, char **argv)
{
	t_parent	parent;
	t_philo		*philo;

	if (argc < 5 || argc > 6) //TODO: create a check function for each arg
		exit_philo(NULL, NULL, NBR_ARGUMENTS);
	check_invalid_args(argc, argv);
	ft_bzero(&parent, sizeof(t_parent));
	parent.number_of_philo = ft_atoi(argv[1]);
	philo_spawn(&philo, &parent);
	parent_init(&parent, philo, argv, argc);
	philo_init(&parent, philo);
	init_mutex(&parent);
	init_threads(&parent, philo);
	wait_threads(&parent);
	destroy_threads(&parent);
	exit_philo(&parent, &philo, NULL);
}