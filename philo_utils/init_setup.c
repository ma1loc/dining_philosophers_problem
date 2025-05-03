# include "_philo.h"

t_setup	*init_setup(int argc, char **argv)
{
	t_setup	*setup;
	t_gc	*gc;

	gc = gc_init();
	setup = gc_malloc(gc, sizeof(t_setup));
	if (!setup)
		return (cleanup_and_exit(setup, "[-] Error:"\
		" malloc failed.\n"), NULL);
	memset(setup, 0, sizeof(t_setup));
	setup->gc = gc;
	input_parsing(argc, argv, setup);
	return (setup);
}

void	setup_user_args(t_setup *setup, char **argv)
{
	setup->user_args = gc_malloc(setup->gc, sizeof(t_user_args));
	if (!setup->user_args)
		cleanup_and_exit(setup, "[-] Error: malloc failed.\n");	// use cleanup_and_exit
	setup->user_args->nbr_of_philo = ft_atoi(argv[1], setup);
	setup->user_args->time_to_die = ft_atoi(argv[2], setup);
	setup->user_args->time_to_eat = ft_atoi(argv[3], setup);
	setup->user_args->time_to_sleep = ft_atoi(argv[4], setup);
	setup->user_args->must_eat_meals = -1;
	if (argv[5])
		setup->user_args->must_eat_meals = ft_atoi(argv[5], setup);
}
