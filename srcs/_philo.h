# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_meals;
}	t_user_args;

typedef struct s_setup
{
	t_gc		*gc;
	t_user_args	*user_args;
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
void	cleanup_and_exit(t_setup *setup, char *msg);


# endif