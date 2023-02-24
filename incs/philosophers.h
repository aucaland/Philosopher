
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>

# define INV_ARGUMENTS	"It work like this : [number of philo] [time to die] \
[time to eat] [time to sleep] [OPTIONAL:nbr of time each philo must eat] "

# ifndef T_ERROR
# define T_ERROR

typedef enum e_error
{
	MALLOC_ERROR = -1,
	ERROR,
	SUCCESS,
}			t_error;

# endif

# ifndef T_BOOL
# define T_BOOL

typedef enum e_bool
{
	FALSE = 0,
	TRUE,
}			t_bool;

# endif


#endif //PHILOSOPHERS_H
