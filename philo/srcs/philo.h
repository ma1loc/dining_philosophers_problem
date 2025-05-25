/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:25:22 by yanflous          #+#    #+#             */
/*   Updated: 2025/05/23 17:25:23 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
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

typedef struct s_gc
{
	t_mem			*mem_list;
	int				total_allocs;
	size_t			total_bytes;
}	t_gc;

typedef struct s_user_args
{
	int		nbr_of_philo;
	int		time_to_die;	
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_meals;
	long	start_time;
}	t_user_args;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*death_mutex;
	int				*someone_died;
	t_user_args		*user_args;
}	t_philo;

typedef struct s_setup
{
	t_gc			*gc;
	t_user_args		*user_args;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	long			start_time;
	int				all_ate_enough;
}	t_setup;

size_t	ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
t_setup	*init_setup(int argc, char **argv);
t_gc	*gc_init(void);
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free(t_gc *gc, void *ptr);
void	gc_destroy(t_gc *gc);
long	get_time_ms(void);
void	ft_usleep(size_t	milliseconds);
void	start_simulation(t_setup *setup);
void	*philo_routine(void *arg);
void	print_status(t_philo *philo, char *status);
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
int		check_someone_died(t_setup *setup);
int		check_all_ate_enough(t_setup *setup, int all_ate_enough);
int		check_philo_died(t_setup *setup, long time_since_last_meal,
			long current_time, int i);
void	philo_delays(t_philo *philo);
int		died_break(t_philo *philo);
void	pickup_forks(t_philo *philo);
void	drop_the_forks(t_philo *philo);
void	cleanup_and_exit(t_setup *setup, char *msg, int destroy_flag);
int		init_philos(t_setup *setup);
int		input_parsing(int argc, char **argv, t_setup *setup);
int		setup_user_args(t_setup *setup, char **argv);
int		ft_atoi(char *str);
void	thinking_time(t_philo *philo);
void	operations(t_philo *philo);
void	update_last_meal_time(t_philo *philo);
void	update_eat_count(t_philo *philo);

#endif
