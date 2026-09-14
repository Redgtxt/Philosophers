# Philosophers

![42 School](https://img.shields.io/badge/42-Lisboa-000000?style=flat-square&logo=42&logoColor=white)
![Milestone](https://img.shields.io/badge/milestone-3-informational?style=flat-square)
![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Threads](https://img.shields.io/badge/pthreads-mutexes-8A2BE2?style=flat-square)
![Norm](https://img.shields.io/badge/norminette-passing-success?style=flat-square)
![Flags](https://img.shields.io/badge/flags-Wall%20%7C%20Wextra%20%7C%20Werror-critical?style=flat-square)

> Dijkstra's dining philosophers, in C, with one thread per philosopher and one mutex per fork — no deadlocks, no starvation, no data races.

Five philosophers sit around a table. Between each pair lies a single fork, and eating requires two. They alternate between eating, sleeping and thinking, and a philosopher who goes too long without a meal dies. The program must run the whole thing concurrently and report every state change with a timestamp, in order, without ever letting two threads write over each other.

The trap is that the naive solution is obviously correct and obviously broken: if every philosopher reaches for their left fork first, all of them succeed, all of them then wait for a right fork nobody will release, and the table deadlocks at timestamp zero. This project is about the gap between "the logic is right" and "the logic is right *under concurrency*".

---

## Table of contents

- [Usage](#usage)
- [Building](#building)
- [Output](#output)
- [Architecture](#architecture)
- [How deadlock is avoided](#how-deadlock-is-avoided)
- [Design notes](#design-notes)
- [Edge cases handled](#edge-cases-handled)
- [What I took away from it](#what-i-took-away-from-it)

---

## Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
| --- | --- |
| `number_of_philosophers` | How many philosophers, and therefore how many forks |
| `time_to_die` | Milliseconds a philosopher may go without starting a meal before dying |
| `time_to_eat` | Milliseconds a meal takes — both forks are held throughout |
| `time_to_sleep` | Milliseconds spent sleeping after a meal |
| `number_of_times_each_philosopher_must_eat` | Optional. The simulation stops once everyone reaches this count |

All times are in milliseconds. When the optional argument is omitted, the simulation runs until someone dies.

```bash
./philo 5 800 200 200        # runs indefinitely, nobody should die
./philo 5 800 200 200 7      # stops once all five have eaten 7 times
./philo 4 410 200 200        # tight margin — a correct scheduler survives, a sloppy one does not
./philo 1 800 200 200        # one philosopher, one fork: dies at 800ms by definition
./philo 5 60 60 60           # someone must die; the death must be reported within 10ms
```

## Building

```bash
make        # builds ./philo
make clean  # removes obj/
make fclean # removes obj/ and the binary
make re     # fclean + all
```

Compiled with `-Wall -Wextra -Werror`. The `Makefile` builds into `obj/`, prints coloured per-file progress, and declares its phony targets.

## Output

One line per state change, each prefixed by milliseconds elapsed since the simulation started:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 has taken a fork
...
812 4 is dead
```

Once a death is printed, nothing else is. The `is dead` line is the last thing the program writes.

## Architecture

Two structures split the problem into "what the whole table knows" and "what one philosopher knows":

```c
t_philo    /* the simulation: parameters, thread handles, the fork array,
              the running flag, and the print mutex                       */

t_worker   /* one philosopher: id, its two fork pointers, last_meal_time,
              meal count, full flag, and a mutex protecting its own state */
```

```
                    ┌──────────────────────────────┐
                    │        t_philo (table)       │
                    │  is_simulation_running       │
                    │  protect_print ──────────────┼── guards stdout + the flag
                    │  mutex_arr[n]  ──────────────┼── one mutex per fork
                    └───────┬──────────────────────┘
                            │
        ┌───────────────────┼───────────────────┐
        ▼                   ▼                   ▼
  ┌───────────┐       ┌───────────┐       ┌───────────┐     ┌──────────────┐
  │ worker 1  │       │ worker 2  │  ...  │ worker n  │     │   monitor    │
  │ thread    │       │ thread    │       │ thread    │     │   thread     │
  │ protect_  │       │ protect_  │       │ protect_  │     │              │
  │  time     │       │  time     │       │  time     │     │ polls every  │
  └─────┬─────┘       └─────┬─────┘       └─────┬─────┘     │    100µs     │
        │                   │                   │           └──────┬───────┘
        └───── eat / sleep / think loop ────────┘                  │
                            ▲                                      │
                            └──────── kill_simulation() ───────────┘
```

`n + 1` threads in total: one per philosopher running `routine`, plus a monitor. Three classes of lock:

| Lock | Protects |
| --- | --- |
| `mutex_arr[i]` | Fork `i` — the resource itself |
| `protect_print` | `stdout` **and** the `is_simulation_running` flag |
| `worker[i].protect_time` | That philosopher's `last_meal_time`, `n_meals` and `is_full` |

The philosophers never read each other's state; only the monitor does, and always through `protect_time`. That is what keeps the design free of races without a single global lock serialising the whole table.

## How deadlock is avoided

Three mechanisms stack:

**1. Asymmetric fork ordering.** `eat()` always locks `right_fork` and then `left_fork` — but which physical mutex is "right" depends on parity:

```c
/* odd id  */  left  = mutex_arr[id - 1];   right = mutex_arr[id % n];
/* even id */  right = mutex_arr[id - 1];   left  = mutex_arr[id % n];
```

Odd philosophers therefore acquire forks in ascending index order and even philosophers in descending order. Breaking the symmetry breaks the circular wait, which is the condition a deadlock cannot do without. It is Dijkstra's own resource-hierarchy answer, expressed as a parity check instead of a comparison.

**2. A staggered start.** `determine_wait_time` delays odd-id philosophers by one `time_to_eat` before their first attempt, so the table does not open with every thread grabbing simultaneously. With an odd number of philosophers the last one waits two `time_to_eat`, since an odd table has no clean two-group alternation.

**3. Padded thinking.** `think()` does not return immediately. It sleeps for the difference between the eating and sleeping phases — doubled when the philosopher count is odd — so that the cycle length stays aligned with fork availability instead of drifting into contention. This is what keeps `./philo 5 800 200 200` alive indefinitely rather than merely usually.

## Design notes

- **The sleep is interruptible.** `ft_usleep` does not call `usleep(ms * 1000)` and hope. It spins in 10µs steps, re-checking both the elapsed time and the simulation flag:

  ```c
  while (get_time() - start_time < time && is_running(worker))
      usleep(10);
  ```

  Two reasons. `usleep` is only guaranteed to sleep *at least* as long as asked, and oversleeping a 200ms meal past an 210ms deadline is how a correct-looking simulation reports a death 30ms late. And a philosopher mid-sleep when someone else dies stops immediately instead of waking up to print a line after the `is dead` message.

- **Timestamps are relative and computed once.** `get_time()` keeps a static origin set on its first call and returns milliseconds since then, so every line in the log shares one clock and the first event is at `0`.

- **The print mutex guards the flag too.** `print_philo` checks `is_simulation_running` and writes the line inside the *same* critical section. Checking the flag and then printing under a separate lock would leave a window where a thread passes the check, the monitor declares a death, and the stale line prints after `is dead`. Folding the two together closes it.

- **Per-philosopher state locks, not one big one.** `last_meal_time` and `n_meals` get a mutex per philosopher rather than a shared one, so the monitor's sweep across the table never serialises philosophers against each other.

- **The monitor polls at 100µs.** Fine enough to report a death well inside the 10ms the subject allows, coarse enough not to burn a core fighting the philosophers for cache lines.

- **Failures unwind in reverse.** Every init step — mutex array, worker array, thread creation — destroys and frees what the previous steps allocated before returning `-1`. A `pthread_create` failure halfway through the table kills the simulation and joins the threads that already started.

## Edge cases handled

| Case | Behaviour |
| --- | --- |
| One philosopher | Takes their single fork, waits, and dies at `time_to_die` — there is no second fork to wait for. Special-cased in both `eat` and the monitor. |
| Everyone has eaten enough | The monitor counts `is_full` philosophers and ends the simulation cleanly when the count reaches `n`. |
| Non-numeric or negative arguments | Rejected during parsing, with a message naming the offending argument and character. A lone `+` is rejected too. |
| Values above `INT_MAX` | Rejected by the custom `ft_atoi`. |
| Wrong argument count | Rejected before anything is allocated. |

## What I took away from it

- That "works on my machine" and "works" are different claims under concurrency: a program with a race condition passes most runs. The bug is in the schedule, not in the code path you read.
- Why the circular-wait condition is the one worth attacking — mutual exclusion, hold-and-wait and no-preemption are all inherent to forks, but the ordering is free to change.
- `pthread_create` / `pthread_join` / `pthread_mutex_*`, and the fact that a mutex protects an *invariant*, not a variable: `last_meal_time` and `is_full` share a lock because they are read together.
- That `usleep` is a lower bound, and that anything time-sensitive needs its own measured loop.
- Designing shutdown as deliberately as startup — a flag everyone polls, a sleep that can be cut short, and a print path that refuses to write after the end.

---

**Author** — Hugo Pinto ([`hguerrei`](https://profile.intra.42.fr/users/hguerrei) · [@Redgtxt](https://github.com/Redgtxt))
