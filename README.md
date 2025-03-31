# Philosophers

Philosophers is a project that explores concurrent programming and synchronization issues using threads and mutexes in C. It is inspired by the famous **Dining Philosophers Problem**, which demonstrates resource sharing and deadlock prevention.

## Problem Statement  
Several philosophers sit at a circular table, each with a fork on their left and right. To eat, a philosopher must pick up both forks. The challenge is to avoid deadlocks and ensure proper synchronization.

## Features  
- Implementation of the **Dining Philosophers Problem** using **threads** and **mutexes**.  
- Proper **handling of concurrency** to avoid deadlocks.  
- Management of **resource sharing** while ensuring each philosopher gets a chance to eat.  

## Requirements  
- A UNIX-based system  
- A C compiler (`gcc` or `clang`)  
- `make` for compilation  
- **pthread** library for thread management  

## 🔧 Installation & Compilation  
Clone the repository and compile the project:  
```sh
cd philosophers
make
```

## Usage  
Run the program with the following arguments:  
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
### Example:  
```sh
./philo 5 800 200 200
```
- `5` → Number of philosophers  
- `800` → Time (in ms) before a philosopher dies without eating  
- `200` → Time (in ms) required to eat  
- `200` → Time (in ms) required to sleep  

If the optional argument `[number_of_times_each_philosopher_must_eat]` is provided, the simulation stops once all philosophers have eaten the required number of times.

## Bonus Features
[ ] **philo_one**: Implementation using only **mutexes**.  
[ ] **philo_two**: Implementation using **semaphores** instead of mutexes. 

---
