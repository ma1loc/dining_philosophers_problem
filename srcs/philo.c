# include "philo.h"

// done //

// • When a philosopher has finished eating, they put their forks back on the table and start sleeping.
// >>> what is have to do when i have one philo ???
// >>> void	singal_philo(t_setup *setup)
// >>> void	muliple_philo(t_setup *setup)
// >>> The number of philosophers and also the number of forks.
// >>> philo -> thread
// >>> fork -> mutex
// >>> thread must have two mutex????
// >>> The second argument in pthread_mutex_init(&mutex, NULL) is for mutex attributes.
// philo 4 500 300 300 -> dea
// philo 5 800 200 200 -> not dea
// philo 4 410 200 200 3 -> dea (not dea, but i stop) to fix
// philo 2 120 60 60 -> not dea (to fix)

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char **argv)
{
    t_setup *setup;

    setup = init_setup(argc, argv);
    if (!setup)
        return (1);
    start_simulation(setup);
    gc_destroy(setup->gc);
    return (0);
}
