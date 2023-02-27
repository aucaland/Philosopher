
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

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

# ifndef T_PHILO
#define T_PHILO

typedef struct s_philo
{
	struct s_parent	*parent_back;
	pthread_t	fork;
	t_bool		is_alive;
	int			philo_nbr;
}				t_philo;

# endif



typedef struct s_parent
{
	t_philo		*philo;
	int			number_of_philo;
}				t_parent;

//		UTILS 			////////////////////////////////////////////////////////
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_free(void *ptr);

//		EXIT			////////////////////////////////////////////////////////
void		exit_malloc(t_parent *parent);

//		PHILOSOPHERS	////////////////////////////////////////////////////////


#endif //PHILOSOPHERS_H
