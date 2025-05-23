#include "philo.h"

int	is_valid_digits(char **argv, t_setup *setup)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (cleanup_and_exit(setup, "[-] Error: args Not"\
				" a valid number.\n", 0), 1);
		i++;
	}
	return (0);
}

int	is_invalid_input(char *str)
{
	size_t	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] && ((str[i] == ' ')
		|| (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && ((str[i] == ' ')
		|| (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	input_parsing(int argc, char **argv, t_setup *setup)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)	
		return (cleanup_and_exit(setup, "[-] Error: Number of args"\
			" not correct.\n", 0), 1);
	while (argv[i])
	{
		if (is_invalid_input(argv[i]))
			return (cleanup_and_exit(setup, "[-] Error: The args"\
				" syntax not correct.\n", 0), 1);
		i++;
	}
	if (is_valid_digits(argv, setup))
		return (1);
	return (0);
}
