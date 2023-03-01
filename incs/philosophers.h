
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "errors.h"
# include <pthread.h>
# include <unistd.h>

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
	unsigned long long int 			time_to_die;
	unsigned long long int 			time_to_eat;
	unsigned long long int 			time_to_sleep;
	int 			must_eat;
	t_state			state;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_t		*threads;
}				t_parent;

//		UTILS 			////////////////////////////////////////////////////////
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_free(void *ptr);
void		ft_usleep(unsigned long long time);
unsigned long long int timer();

//		EXIT			////////////////////////////////////////////////////////
void		exit_philo(t_parent *parent, char *msg);

//		PHILOSOPHERS	////////////////////////////////////////////////////////
void		print(t_philo *philo, t_state	state);
void		unlock(int which_forks, t_parent *parent, t_philo *philo);

//		PHILO_STATES	////////////////////////////////////////////////////////
void		sleeping(t_philo *philo);
void		eating(t_philo *philo);
void		thinking(t_philo *philo);
void		take_fork(t_philo *philo);
void		check_death_before_silence(t_philo *philo, t_state state);
//		CHECK_INV_ARGS	////////////////////////////////////////////////////////
void		check_invalid_args(int argc, char **argv);

#endif //PHILOSOPHERS_H
