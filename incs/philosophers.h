
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "errors.h"

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

typedef struct s_philo
{
	int 		own_fork;
	int 		lfork;
	t_bool		is_alive;
	t_bool		is_sleeping;
	t_bool		is_eating;
	int			philo_nbr;
}				t_philo;

typedef struct s_parent
{
	t_philo			*philo;
	int				number_of_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			meals_min;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}				t_parent;

//		UTILS 			////////////////////////////////////////////////////////
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_free(void *ptr);

//		EXIT			////////////////////////////////////////////////////////
void		exit_philo(t_parent *parent, char *msg);

//		PHILOSOPHERS	////////////////////////////////////////////////////////

//		CHECK_INV_ARGS	////////////////////////////////////////////////////////
void		check_invalid_args(int argc, char **argv);

#endif //PHILOSOPHERS_H
