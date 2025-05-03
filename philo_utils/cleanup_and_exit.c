# include "_philo.h"

void	cleanup_and_exit(t_setup *setup, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	gc_destroy(setup->gc);
	exit(1);
}