# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

typedef struct	s_gc
{
	t_mem			*mem_list;
	int				total_allocs;
	size_t			total_bytes;
}	t_gc;

typedef struct	s_user_args
{
	int	nbr_of_philo;	// >>> number of the philo (thread)
	int	time_to_die;	
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_meals;	// >>> option -> how much the phlos must eating
}	t_user_args;

typedef	struct	s_philo
{
	int				id;				// >>> just a number of the philo(X)
	int				eat_count;		// >>> track how much time take each philo to eat
	long			last_meal_time;	// >>> to get the last meal time. check it in every thread, in the first time have to set to 0, if the current time > time last_meal = dea
	pthread_t		thread;			// >>> hold id of the thread
	pthread_mutex_t	*left_fork;		// >>> left fork(thread) 
	pthread_mutex_t	*right_fork;	// >>> right fork(thread)
	pthread_mutex_t	*print_mutex;	// >>> ensures only one thread prints at a time.
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*death_mutex;
	int				*someone_died;
}	t_philo;

typedef struct s_setup
{
	t_gc			*gc;
	t_user_args		*user_args;
	t_philo			*philo;
	// >>>>>>>>>>>>>>>>>>>>>>>>
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;	// >>> ensures only one thread prints at a time.
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	// >>>>>>>>>>>>>>>>>>>>>>>>
} t_setup;

int		ft_atoi(char *str, t_setup *setup);
size_t	ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
t_setup	*init_setup(int argc, char **argv);
void	setup_user_args(t_setup *setup, char **argv);
t_gc	*gc_init(void);
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free(t_gc *gc, void *ptr);
void	gc_destroy(t_gc *gc);
void	input_parsing(int argc, char **argv, t_setup *setup);
void	cleanup_and_exit(t_setup *setup, char *msg, int stat);
long	get_time_ms(void);
void	singal_philo(t_setup *setup);
void	sleep_ms(int ms);

# endif