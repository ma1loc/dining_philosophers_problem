# include "_philo.h"

// Each philosopher should be a thread.

void	singal_philo(t_setup *setup)
{
	// what is have to do when i have one philo ???
}

int	main(int argc, char **argv)
{
	t_setup	*setup;

	setup = init_setup(argc, argv);
	if (!setup)
		return (1);
	setup_user_args(setup, argv);
	// >>>> here >>>>
	if (setup->user_args->nbr_of_philo == 1)	// case of one philo.
		singal_philo(setup);
	else
		multiple_philo(setup);
	// >>>>>>>>>>>>>>
	gc_destroy(setup->gc);
}
