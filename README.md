# Philosophers - Dining Philosophers Problem

A multithreaded simulation of the classic **Dining Philosophers Problem** implemented in C using POSIX threads and mutexes.

## 📖 Problem Description

The Dining Philosophers Problem is a classic synchronization problem in computer science that illustrates the challenges of avoiding deadlock and resource starvation in concurrent programming.

**The Scenario:**
- N philosophers sit around a circular table
- Each philosopher alternates between thinking, eating, and sleeping
- There are N forks placed between the philosophers (one between each pair)
- A philosopher needs **two forks** (left and right) to eat
- Philosophers cannot communicate with each other
- The simulation ends when a philosopher dies of starvation

## 🎯 Objectives

- Implement proper synchronization using mutexes
- Prevent deadlock situations
- Avoid race conditions
- Monitor philosopher states and detect death
- Handle the special case of a single philosopher

## 🚀 Features

- **Multithreaded simulation** with one thread per philosopher
- **Monitor thread** to detect death and completion conditions
- **Mutex-based synchronization** for forks and shared resources
- **Custom garbage collector** for memory management
- **Precise timing** using microsecond precision
- **Deadlock prevention** through ordered resource acquisition

## 📋 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameters | Description | Range |
|------------|-------------|-------|
| `number_of_philosophers` | Number of philosophers (and forks) | 1-200 |
| `time_to_die` | Time in ms after which a philosopher dies if they haven't eaten | > 0 |
| `time_to_eat` | Time in ms it takes for a philosopher to eat | > 0 |
| `time_to_sleep` | Time in ms a philosopher spends sleeping | > 0 |
| `number_of_times_each_philosopher_must_eat` | *Optional* - Simulation stops when all philosophers have eaten at least this many times | > 0 |

### Examples

```bash
# Basic simulation with 4 philosophers
./philo 4 800 200 200

# Simulation that ends when each philosopher has eaten 5 times
./philo 5 800 200 200 5

# Edge case: Single philosopher (will die)
./philo 1 800 200 200

# Quick death scenario
./philo 4 310 200 100
```

## 🔧 Key Components

### Data Structures

- **`t_philo`**: Individual philosopher with ID, meal count, timing, and mutex references
- **`t_setup`**: Global simulation setup containing all philosophers, forks, and shared data
- **`t_user_args`**: User input parameters and timing configuration
- **`t_gc`**: Garbage collector for automated memory management

### Synchronization

- **Fork mutexes**: One per fork to prevent simultaneous access
- **Print mutex**: Ensures atomic output printing
- **Meal mutex**: Protects meal timing and count updates
- **Death mutex**: Synchronizes death detection across threads

### Deadlock Prevention

The program prevents deadlock through:
1. **Ordered resource acquisition**: Always acquire lower-numbered fork first
2. **Staggered start times**: Even-numbered philosophers start with a delay
3. **Proper mutex unlocking order**: Consistent unlock sequence

## 🎮 Output Format

The simulation outputs timestamped status messages:

```
timestamp_in_ms philosopher_id status
```

**Status messages:**
- `is thinking`
- `has taken a fork`
- `is eating`
- `is sleeping`
- `died`

**Example output:**
```
0 1 is thinking
0 3 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
200 1 is sleeping
200 3 has taken a fork
200 3 is eating
400 1 is thinking
400 3 is sleeping
```

## ⚙️ Compilation

```bash
# Compile the project
make

# Clean object files
make clean

# Full clean (remove executable)
make fclean

# Recompile everything
make re
```

**Compiler flags used:**
- `-Wall -Wextra -Werror`: Strict error checking
- `-pthread`: POSIX threads support
- `-g`: Debug information

## 🧪 Testing Scenarios

### Basic Tests
```bash
./philo 1 800 200 200        # Should die (can't eat with one fork)
./philo 5 800 200 200        # Normal simulation
./philo 4 410 200 200        # Should die quickly
./philo 4 800 200 200 7      # Stop after 7 meals each
```

### Stress Tests
```bash
./philo 200 800 200 200      # Maximum philosophers
./philo 4 80 50 50           # Very tight timing
./philo 2 60 50 50           # Minimal viable timing
```

## 🐛 Common Issues & Solutions

### Deadlock
- **Cause**: Circular wait for resources
- **Solution**: Ordered resource acquisition (lower-numbered fork first)

### Race Conditions
- **Cause**: Unsynchronized access to shared data
- **Solution**: Proper mutex usage around critical sections

### Data Races
- **Cause**: Simultaneous read/write to shared variables
- **Solution**: Mutex protection for all shared data access

### Timing Issues
- **Cause**: Imprecise sleep functions
- **Solution**: Custom `ft_usleep()` with busy-wait for accuracy

## 🔍 Algorithm Overview

1. **Initialization**: Parse arguments, create philosophers and forks
2. **Thread Creation**: Start philosopher threads and monitor thread
3. **Philosopher Loop**:
   - Think → Try to pick up forks → Eat → Drop forks → Sleep → Repeat
4. **Monitor Loop**: Check for death conditions and meal completion
5. **Cleanup**: Join threads and free resources

## 📚 Educational Value

This project demonstrates:
- **Concurrent Programming**: Multiple threads working simultaneously
- **Synchronization Primitives**: Mutexes for thread safety
- **Deadlock Prevention**: Resource ordering and timing strategies
- **Resource Management**: Custom memory allocator
- **Systems Programming**: Low-level threading and timing

## 🔗 References

- [My summery](https://www.tldraw.com/f/C6-inD4k34iMIawSGyDxY?d=v-7887.-5255.19180.9280.oqn2CHo79BTggCUf3hyLE)
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [The Little Book of Semaphores](http://greenteapress.com/semaphores/)

---

**Note**: This implementation is part of the 42 School curriculum and follows strict coding standards including the 42 Norm.
