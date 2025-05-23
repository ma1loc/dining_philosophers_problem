# include "philo.h"

int main(int argc, char **argv)
{
    t_setup	*setup;

    setup = init_setup(argc, argv);
    if (!setup)
        return (1);
    start_simulation(setup);
    cleanup_and_exit(setup, NULL, 1);
    return (0);
}
