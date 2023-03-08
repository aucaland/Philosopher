/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:48:17 by aurel             #+#    #+#             */
/*   Updated: 2023/03/08 11:17:04 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	ERRORS_H
#define ERRORS_H

# include "philosophers.h"

# define NBR_ARGUMENTS		"It work like this : [number of philo] [time to \
die] [time to eat] [time to sleep] [OPTIONAL:nbr of time each philo must eat] "
# define NBR_PHILOS			"[Number of philo] must be a positiv int"
# define FAILED_ALLOC		"Allocation failed"
# define NBR_MEAL			"Philos can't eat less than 0 time, obviously"
# define FAILED_THREAD		"Failed to create a thread"
# define INV_DIGIT			"Arguments must be positive or null numbers"
# define NEGATIV_PHILO_NBR	"There must be at least 1 Philosopher"

# define SLEEPING_MSG		"is sleeping"
# define THINKING_MSG		"is thinking"
# define EATING_MSG			"is eating"
# define TAKING_FORK_MSG	"has taken a fork"
# define DYING_MSG			"died"

# define BOTH_FORKS			10
# define LEFT_FORK			11
# define RIGHT_FORK			12
# define OWN_FORK			13

#endif //ERRORS_H
