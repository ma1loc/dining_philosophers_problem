#include "_philo.h"

// parasing philo Test
// ./philo 1+1 1 1 1

int	is_valid_digits(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		printf("before argv[%d] -> %s\n", i, argv[i]);
		printf("ft_atoi(argv[%d] -> %d\n", i, ft_atoi(argv[i]));
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("[-] Error: argv[%d] -> \"%s\" Not a valid number.\n", i, argv[i]);
			return (1);
		}
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
	while (str[i] && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	input_parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (printf("[-] Error: Number of args not currect.\n"), 1);
	while (argv[i])
	{
		if (is_invalid_input(argv[i]))
		{
			printf("[-] Error: The args[%d] -> \"%s\" syntax not currect.\n", i, argv[i]);
			return (1);
		}
		i++;
	}
	if (is_valid_digits(argv))
		return (1);
	return (0);
}
