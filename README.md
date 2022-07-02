# Philosophers
https://cdn.intra.42.fr/pdf/pdf/52133/fr.subject.pdf

## TODO

1. rewrite [eat](./philo_bonus/life/ft_eat.c), forks are everywere
2. finishe [waiter](./philo_bonus/life/ft_wait.c)
3. add signal handler with kill (see [here](http://manpagesfr.free.fr/man/man2/kill.2.html))
	- kill all child when one have died
		- kill if it's there with return value of kill
	- singal handler to world
	- maybe rename death god
4. review all the world code
	- review semaphore used
		- memory NOT shared between philos, therefore some semaphore maybe useless
	- check if starved or all ate in world, and death will kill (with the command)
<br>
	all the other process

