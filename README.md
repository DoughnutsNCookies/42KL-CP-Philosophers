# Philosophers

Philosophers provided a learning experience in multithreading and multiprocessors in C, where I explored concurrent programming concepts.

By recreating the dining philosophers' problem, I was able to delve into the challenges of synchronizing multiple threads or processes to avoid deadlocks and ensure fair resource allocation.


## Project Demo
![Project Demo](https://github.com/DoughnutsNCookies/42KL-CP-Philosophers/blob/main/readmeAssets/Philosophers-gif.gif)


## Dining Philosophers Problem
A group of `N` philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.

The philosophers alternatively `eat`, `think`, or `sleep`.
  - While `eating`, they are not `thinking` or `sleeping`
  - While `thinking`, they are not `eating` or `sleeping`;
  - While `sleeping`, they are not `eating` or `thinking`.

There are also forks on the table. There are as many forks as philosophers.
  - A philosopher takes their `right` and their `left` forks to `eat`, `one in each hand`.
  - When a philosopher has finished eating, they `put their forks back on the table` and start `sleeping`.
  - Once awake, they start `thinking` again. The simulation `stops` when a philosopher `dies` of starvation.

Every philosopher needs to `eat` and should `never starve`.

Philosophers don’t speak with each other.

Philosophers don’t know if another philosopher is about to `die`.

No need to say that philosophers `should avoid dying`!


## Mandatory
The mandatory part of this project is mainly about `threads` and `mutexes`.

Each philosopher will be a `thread`, and each fork will be a `mutex`.

**Thread**
- `Threads` are the smallest units of a process that an operating system can schedule for execution.
- They enable a program to perform `multiple tasks simultaneously`, `sharing the same memory and resources`, which makes them more efficient than separate processes. 

**Mutex**
- `Mutex`, short for mutual exclusion, is a synchronization mechanism used in multi-threaded programming to ensure that `only one thread can access a specific resource` or `critical section of code at a time`.
- `Mutexes prevent data races` and maintain data integrity by allowing threads to take turns accessing shared resources in an orderly manner.


## Bonus
The bonus part of this project is mainly about `processes` and `semaphores`.

Each philosopher will be a `process`, and each fork will be a `semaphore`.

The forks are all put in the `middle of the table` instead of between each philosopher

**Process**
- `Processes` are independent units of execution with their `own memory space and resources`, providing strong isolation between them.

**Semaphore**
- `Semaphores` are synchronization mechanisms used to `manage access to shared resources` in multi-threaded and multi-process environments.
- They come in binary and counting types, facilitating `controlled access and coordination` among threads or processes.


## Data Racing
`Data races` occur in multi-threaded programs when two or more threads `concurrently access and manipulate shared data` without proper synchronization mechanisms. 

This can lead to `unpredictable and erroneous behavior` in a program because the threads' operations can interfere with each other.


## Deadlock
`Deadlock` is a situation where `multiple threads or processes` are caught in a `circular waiting pattern`, each holding resources needed by another, which leads to a `standstill where no progress can be made`.

It's a critical issue in concurrent programming that requires careful design and the use of synchronization mechanisms like `semaphores` or `mutexes` to prevent or resolve.


## Authors
- [@DoughnutsNCookies](https://www.github.com/DoughnutsNCookies)

