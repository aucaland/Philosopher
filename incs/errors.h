/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:48:17 by aurel             #+#    #+#             */
/*   Updated: 2023/02/28 15:48:17 by aurel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	ERRORS_H
#define ERRORS_H

# include "philosophers.h"

# define NBR_ARGUMENTS	"It work like this : [number of philo] [time to die] \
[time to eat] [time to sleep] [OPTIONAL:nbr of time each philo must eat] "
# define NBR_PHILOS		"[Number of philo] must be a positiv int"
# define FAILED_ALLOC	"Allocation failed"
# define NBR_MEAL		"Philos can't eat less than 0 time, obviously"

#endif //ERRORS_H
