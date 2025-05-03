# include "_philo.h"

void	setup_user_args(t_setup *setup, char **argv)
{
	setup->user_args = gc_malloc(setup->gc, sizeof(t_user_args));
	if (!setup->user_args)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n");	// use cleanup_and_exit
	setup->user_args->nbr_of_philo = ft_atoi(argv[1]);
	setup->user_args->time_to_die = ft_atoi(argv[2]);
	setup->user_args->time_to_eat = ft_atoi(argv[3]);
	setup->user_args->time_to_sleep = ft_atoi(argv[4]);
	setup->user_args->max_meals = -1;
	if (argv[5])
		setup->user_args->max_meals = ft_atoi(argv[5]);
}	

t_setup	*init_setup(int argc, char **argv)
{
	t_setup	*setup;
	t_gc	*gc;

	gc = gc_init();
	setup = gc_malloc(gc, sizeof(t_setup));
	if (!setup)
		return (cleanup_and_exit(setup, "[-] Error: malloc failed.\n"), NULL);
	// memset(setup, 0, sizeof(t_setup));
	setup->gc = gc;
	if (input_parsing(argc, argv))
		return (gc_destroy(setup->gc), NULL);
	return (setup);
}

int	main(int argc, char **argv)
{
	t_setup	*setup;

	setup = init_setup(argc, argv);
	if (!setup)
		return (1);
	setup_user_args(setup, argv);
	
}
