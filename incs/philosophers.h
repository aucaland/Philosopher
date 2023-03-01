
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

typedef enum e_state
{
	TAKING,
	EATING,
	SLEEPING,
	THINKING,
	WAITING,
	DEAD,
}			t_state;

typedef struct s_parent	t_parent;
typedef struct s_philo
{
	t_parent	*parent_call;
	int 		own_fork;
	int 		lfork;
	int 		last_eat;
	int 		eat_count;
	t_state		state;
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
	t_state			state;
	pthread_mutex_t	*fork;
	pthread_t		*threads;
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
