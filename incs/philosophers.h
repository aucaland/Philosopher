
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

typedef enum e_bool
{
	FALSE,
	TRUE,
}			t_bool;

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
	int 		rfork;
	unsigned long long 		last_eat;
	int 		eat_count;
	t_state		state;
	int			philo_nbr;
}				t_philo;

typedef struct s_parent
{
	t_philo			*philo;
	t_state			state;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	state_mutex;
	pthread_t		*threads;
	int				number_of_philo;
	int 			must_eat;
	unsigned long long int 			time_to_die;
	unsigned long long int 			time_to_eat;
	unsigned long long int 			time_to_sleep;
}				t_parent;

//		UTILS 			////////////////////////////////////////////////////////
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_free(void *ptr);
void		ft_usleep(unsigned long long time);
unsigned long long int timer();

//		EXIT			////////////////////////////////////////////////////////
void		exit_philo(t_parent *parent, t_philo **philo, char *msg);

//		PHILOSOPHERS	////////////////////////////////////////////////////////
void		print(t_philo *philo, t_state	state);
void		unlock(int which_forks, t_parent *parent, t_philo *philo, t_bool
ODD);
void		routine(t_philo *philo);

//		PHILO_STATES	////////////////////////////////////////////////////////
void		sleeping(t_philo *philo);
void		eating(t_philo *philo);
void		thinking(t_philo *philo);
void		take_fork(t_philo *philo);
void		check_death_before_silence(t_philo *philo, t_state state);
char		*state_msg(t_state state);
void		dying(t_philo *philo, unsigned long long time_to_wait);
//		CHECK_INV_ARGS	////////////////////////////////////////////////////////
void		check_invalid_args(int argc, char **argv);

//		INIT			////////////////////////////////////////////////////////
void		philo_spawn(t_philo	**philo, t_parent *parent);
void		parent_init(t_parent *parent, t_philo *philo, char **argv, int
argc);
void		philo_init(t_parent *parent, t_philo *philo);
void		init_threads(t_parent *parent, t_philo *philo);
void		init_mutex(t_parent *parent);

//		GET				////////////////////////////////////////////////////////
unsigned long long	time_to_eat(t_philo *philo);
unsigned long long	time_to_die(t_philo *philo);
unsigned long long	time_to_sleep(t_philo *philo);
#endif //PHILOSOPHERS_H
