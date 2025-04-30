# include "philo.h"

t_user_args	*setup_user_args(char **argv)
{
	t_user_args *user_args;

	user_args = malloc(sizeof(t_user_args));
	if (!user_args)
		return (NULL);
	user_args->nbr_of_philo = ft_atoi(argv[1]);
	user_args->time_to_die = ft_atoi(argv[2]);
	user_args->time_to_eat = ft_atoi(argv[3]);
	user_args->time_to_sleep = ft_atoi(argv[4]);
	user_args->max_meals = -1;
	if (argv[5])
		user_args->max_meals = ft_atoi(argv[5]);
	return (user_args);
}	

int	main(int argc, char **argv)
{
	t_user_args	*user_args;

	user_args = NULL;
	if (input_parsing(argc, argv))
		return (1);
	user_args = setup_user_args(argv);
	if (!user_args)
		return (printf("[-] Error: malloc failed.\n"), 1);
}
