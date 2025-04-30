# philosophers

# Complete Guide to the Philosophers Project (42 School)

## Table of Contents
1. [Understanding the Problem](#understanding-the-problem)
2. [Core Concepts You Need to Learn](#core-concepts-you-need-to-learn)
3. [Project Requirements](#project-requirements)
4. [Step-by-Step Implementation Guide](#step-by-step-implementation-guide)
5. [Common Challenges and Solutions](#common-challenges-and-solutions)
6. [Testing Your Implementation](#testing-your-implementation)

## Understanding the Problem

The Dining Philosophers problem is a classic computer science problem that illustrates challenges in resource allocation and concurrent programming:

- N philosophers sit at a round table
- Each philosopher needs two forks to eat (one fork between each philosopher)
- Philosophers alternate between eating, thinking, and sleeping
- If a philosopher doesn't eat for too long, they die
- The simulation stops when a philosopher dies

Your task is to create a program that simulates this scenario without deadlocks (all philosophers waiting for forks) or data races (unsafe shared memory access).

## Core Concepts You Need to Learn

### 1. Threads and Processes

**Threads**:
- Lightweight execution units that share the same memory space
- Created with `pthread_create()`
- Joined with `pthread_join()`
- Each philosopher will be a thread

**Example**:
```c
#include <pthread.h>

void *philosopher_routine(void *arg) {
    // Philosopher actions here
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, philosopher_routine, arg);
    pthread_join(thread_id, NULL);
}
```

### 2. Mutex (Mutual Exclusion)

- Protects shared resources (forks) from concurrent access
- Created with `pthread_mutex_init()`
- Locked with `pthread_mutex_lock()`
- Unlocked with `pthread_mutex_unlock()`
- Destroyed with `pthread_mutex_destroy()`

**Example**:
```c
pthread_mutex_t fork_mutex;

pthread_mutex_init(&fork_mutex, NULL);
pthread_mutex_lock(&fork_mutex);
// Access protected resource (fork)
pthread_mutex_unlock(&fork_mutex);
pthread_mutex_destroy(&fork_mutex);
```

### 3. Semaphores (Optional)

- Similar to mutex but allows multiple threads to access a resource
- Created with `sem_init()`
- Wait operation with `sem_wait()`
- Signal operation with `sem_post()`
- Destroyed with `sem_destroy()`

**Example**:
```c
#include <semaphore.h>

sem_t semaphore;
sem_init(&semaphore, 0, 1); // Initialize with value 1
sem_wait(&semaphore); // Decrement
// Access protected resource
sem_post(&semaphore); // Increment
sem_destroy(&semaphore);
```

### 4. Timing Functions

- Get current time with `gettimeofday()`
- Sleep with `usleep()` (microseconds)

**Example**:
```c
#include <sys/time.h>
#include <unistd.h>

struct timeval current_time;
gettimeofday(&current_time, NULL);
long time_in_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;

usleep(200000); // Sleep for 200 milliseconds
```

## Project Requirements

Typical requirements (confirm with your specific assignment):

1. Global variables must be protected with mutexes
2. Each philosopher has a unique ID (1 to N)
3. Program takes the following arguments:
   - `number_of_philosophers`: Number of philosophers and forks
   - `time_to_die`: Time in milliseconds until a philosopher dies if they haven't eaten
   - `time_to_eat`: Time in milliseconds it takes to eat
   - `time_to_sleep`: Time in milliseconds it takes to sleep
   - `[number_of_times_each_philosopher_must_eat]`: Optional argument, simulation stops when all philosophers have eaten this many times

4. Each state change must be logged with a message:
   - `timestamp_in_ms X has taken a fork`
   - `timestamp_in_ms X is eating`
   - `timestamp_in_ms X is sleeping`
   - `timestamp_in_ms X is thinking`
   - `timestamp_in_ms X died`

## Step-by-Step Implementation Guide

### 1. Parse Command-Line Arguments

```c
typedef struct s_args {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count; // Optional, -1 if not provided
} t_args;

void parse_args(int argc, char **argv, t_args *args) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        exit(1);
    }
    
    args->num_philosophers = atoi(argv[1]);
    args->time_to_die = atoi(argv[2]);
    args->time_to_eat = atoi(argv[3]);
    args->time_to_sleep = atoi(argv[4]);
    args->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
    
    // Validate arguments (no negatives, etc.)
}
```

### 2. Create Data Structures

```c
typedef struct s_philo {
    int id;
    int eat_count;
    long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *meal_mutex;
    int *someone_died;
    pthread_mutex_t *death_mutex;
    t_args *args;
} t_philo;

typedef struct s_simulation {
    t_philo *philosophers;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    int someone_died;
    t_args args;
} t_simulation;
```

### 3. Initialize the Simulation

```c
void init_simulation(t_simulation *sim) {
    int i;
    
    // Allocate memory
    sim->philosophers = malloc(sizeof(t_philo) * sim->args.num_philosophers);
    sim->forks = malloc(sizeof(pthread_mutex_t) * sim->args.num_philosophers);
    
    // Initialize mutexes
    pthread_mutex_init(&sim->print_mutex, NULL);
    pthread_mutex_init(&sim->death_mutex, NULL);
    sim->someone_died = 0;
    
    // Initialize forks
    for (i = 0; i < sim->args.num_philosophers; i++) {
        pthread_mutex_init(&sim->forks[i], NULL);
    }
    
    // Initialize philosophers
    for (i = 0; i < sim->args.num_philosophers; i++) {
        sim->philosophers[i].id = i + 1;
        sim->philosophers[i].eat_count = 0;
        sim->philosophers[i].last_meal_time = get_current_time();
        sim->philosophers[i].left_fork = &sim->forks[i];
        sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim->args.num_philosophers];
        sim->philosophers[i].print_mutex = &sim->print_mutex;
        sim->philosophers[i].meal_mutex = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(sim->philosophers[i].meal_mutex, NULL);
        sim->philosophers[i].someone_died = &sim->someone_died;
        sim->philosophers[i].death_mutex = &sim->death_mutex;
        sim->philosophers[i].args = &sim->args;
    }
}
```

### 4. Philosopher Routine

```c
void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    
    // If odd ID, wait a bit to prevent deadlock
    if (philo->id % 2 == 1)
        usleep(1000);
    
    while (1) {
        // Check if someone died or all philosophers have eaten enough
        pthread_mutex_lock(philo->death_mutex);
        if (*philo->someone_died || 
            (philo->args->must_eat_count != -1 && philo->eat_count >= philo->args->must_eat_count)) {
            pthread_mutex_unlock(philo->death_mutex);
            break;
        }
        pthread_mutex_unlock(philo->death_mutex);
        
        // Think
        print_status(philo, "is thinking");
        
        // Eat (take forks, eat, release forks)
        if (!take_forks(philo))
            break;
        
        eat(philo);
        
        release_forks(philo);
        
        // Sleep
        print_status(philo, "is sleeping");
        precise_sleep(philo->args->time_to_sleep);
    }
    
    return NULL;
}
```

### 5. Fork Management Functions

```c
int take_forks(t_philo *philo) {
    // To prevent deadlock, always take the lower-numbered fork first
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    
    if (philo->id % 2 == 0) {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    } else {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    
    pthread_mutex_lock(first_fork);
    print_status(philo, "has taken a fork");
    
    // If there's only one philosopher, they can't eat
    if (philo->args->num_philosophers == 1) {
        pthread_mutex_unlock(first_fork);
        precise_sleep(philo->args->time_to_die * 2);
        return 0;
    }
    
    pthread_mutex_lock(second_fork);
    print_status(philo, "has taken a fork");
    
    return 1;
}

void release_forks(t_philo *philo) {
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
```

### 6. Eating Function

```c
void eat(t_philo *philo) {
    print_status(philo, "is eating");
    
    // Update last meal time
    pthread_mutex_lock(philo->meal_mutex);
    philo->last_meal_time = get_current_time();
    philo->eat_count++;
    pthread_mutex_unlock(philo->meal_mutex);
    
    precise_sleep(philo->args->time_to_eat);
}
```

### 7. Utility Functions

```c
long get_current_time() {
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void precise_sleep(int milliseconds) {
    long start_time = get_current_time();
    
    while (get_current_time() - start_time < milliseconds)
        usleep(100);
}

void print_status(t_philo *philo, char *status) {
    pthread_mutex_lock(philo->print_mutex);
    pthread_mutex_lock(philo->death_mutex);
    
    if (!*philo->someone_died)
        printf("%ld %d %s\n", get_current_time(), philo->id, status);
    
    pthread_mutex_unlock(philo->death_mutex);
    pthread_mutex_unlock(philo->print_mutex);
}
```

### 8. Death Monitoring

```c
void *death_monitor(void *arg) {
    t_simulation *sim = (t_simulation *)arg;
    int i;
    long current_time;
    
    while (1) {
        for (i = 0; i < sim->args.num_philosophers; i++) {
            pthread_mutex_lock(sim->philosophers[i].meal_mutex);
            current_time = get_current_time();
            
            if (current_time - sim->philosophers[i].last_meal_time > sim->args.time_to_die) {
                pthread_mutex_lock(&sim->print_mutex);
                pthread_mutex_lock(&sim->death_mutex);
                printf("%ld %d died\n", current_time, sim->philosophers[i].id);
                sim->someone_died = 1;
                pthread_mutex_unlock(&sim->death_mutex);
                pthread_mutex_unlock(&sim->print_mutex);
                pthread_mutex_unlock(sim->philosophers[i].meal_mutex);
                return NULL;
            }
            
            // Check if all philosophers have eaten enough
            if (sim->args.must_eat_count != -1) {
                int all_ate_enough = 1;
                
                for (int j = 0; j < sim->args.num_philosophers; j++) {
                    if (sim->philosophers[j].eat_count < sim->args.must_eat_count) {
                        all_ate_enough = 0;
                        break;
                    }
                }
                
                if (all_ate_enough) {
                    pthread_mutex_lock(&sim->death_mutex);
                    sim->someone_died = 1;
                    pthread_mutex_unlock(&sim->death_mutex);
                    pthread_mutex_unlock(sim->philosophers[i].meal_mutex);
                    return NULL;
                }
            }
            
            pthread_mutex_unlock(sim->philosophers[i].meal_mutex);
        }
        
        usleep(1000);
    }
    
    return NULL;
}
```

### 9. Main Function

```c
int main(int argc, char **argv) {
    t_simulation sim;
    pthread_t death_thread;
    int i;
    
    // Parse arguments
    parse_args(argc, argv, &sim.args);
    
    // Initialize simulation
    init_simulation(&sim);
    
    // Create philosopher threads
    for (i = 0; i < sim.args.num_philosophers; i++) {
        pthread_create(&sim.philosophers[i].thread, NULL, philosopher_routine, &sim.philosophers[i]);
    }
    
    // Create death monitoring thread
    pthread_create(&death_thread, NULL, death_monitor, &sim);
    
    // Wait for death monitor to finish
    pthread_join(death_thread, NULL);
    
    // Kill all philosopher threads
    for (i = 0; i < sim.args.num_philosophers; i++) {
        pthread_join(sim.philosophers[i].thread, NULL);
    }
    
    // Clean up resources
    cleanup_simulation(&sim);
    
    return 0;
}
```

### 10. Cleanup Function

```c
void cleanup_simulation(t_simulation *sim) {
    int i;
    
    // Destroy mutex locks
    for (i = 0; i < sim->args.num_philosophers; i++) {
        pthread_mutex_destroy(&sim->forks[i]);
        pthread_mutex_destroy(sim->philosophers[i].meal_mutex);
        free(sim->philosophers[i].meal_mutex);
    }
    
    pthread_mutex_destroy(&sim->print_mutex);
    pthread_mutex_destroy(&sim->death_mutex);
    
    // Free allocated memory
    free(sim->philosophers);
    free(sim->forks);
}
```

## Common Challenges and Solutions

### 1. Deadlock Prevention

The most common deadlock occurs when all philosophers pick up their left fork and wait for the right fork. Solutions:

- **Resource Hierarchy**: Always pick up the lower-numbered fork first
- **Even/Odd Strategy**: Even-numbered philosophers pick up right fork first, odd-numbered pick up left fork first
- **Limited Philosophers**: Only allow N-1 philosophers to eat simultaneously

### 2. Race Conditions

Race conditions occur when multiple threads access shared data concurrently. Solutions:

- Protect all shared variables with mutex locks
- Be careful about lock order to prevent deadlocks
- Use separate mutexes for different resources

### 3. Performance Optimization

- Avoid excessive lock contention
- Use precise timing mechanisms
- Minimize the critical sections (lock/unlock as quickly as possible)

### 4. Death Detection Timing

Ensure death is detected quickly and accurately:
- Regular checks
- Accurate timestamps
- Prevent false positives

## Testing Your Implementation

### Basic Tests

1. **Single Philosopher**: Should die after `time_to_die` milliseconds
2. **Two Philosophers**: Should be able to eat alternately without dying
3. **Normal Case**: With sufficient time parameters, no philosopher should die

### Edge Cases

1. **Large Number of Philosophers**: Test with a large number (e.g., 200)
2. **Minimal Time Values**: Test with very small time values
3. **Optional Argument**: Test with the optional "must eat" count
4. **Argument Validation**: Test with invalid arguments (negative values, etc.)

### Performance Testing

1. **Resource Usage**: Monitor CPU and memory usage
2. **Timing Accuracy**: Verify that philosophers die at the correct time
3. **Race Conditions**: Run multiple instances simultaneously to test for race conditions

## Conclusion

The Philosophers project is an excellent way to learn about concurrent programming, thread synchronization, and resource allocation. The key to success is understanding mutexes, careful implementation of the philosopher routines, and proper death monitoring.

Remember to test thoroughly and handle edge cases properly. Good luck with your implementation!