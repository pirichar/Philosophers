#! /bin/bash

# argv[0] = Program
# argv[1] = number_of_philosophers 
# 	(if only ony the philosopher has to die at some point)
# argv[2] = time_to_die time_to_die (en millisecondes)
# argv[3] = time_to_eat (en milisecondes)
# argv[4] = time_to_sleep (en milisecondes )
# argv[5] = number_of_times_each_philosopher_must_eat (optionnel 
# gcc -Wall -Werror -Wextra -g ./src/*.c
make re
# for i in {0..50}; do ./test.sh; done;
# ./philo 2 400 200 200 
# ./philo 2 401 200 200 
# ./philo 3 600 200 200 
# ./philo 3 601 200 200 
# ./philo 3 601 200 200 5
# ./philo 4 401 200 200 
# ./philo 6 401 200 200 
# ./philo 5 620 200 200
# ./philo 7 800 200 200
# ./philo 3 601 200 200 5
# 0		1	2	3	4 5


# tests de correction
#test avec 200 philos
# ./philo 199 800 200 200
#this should die
# ./philo 1 800 200 200
#this should run
# ./philo 5 800 200 200
#this should run untill 7
# ./philo 5 800 200 200 7
#no one should die
./philo 4 410 200 200
#someone should die
# ./philo 4 310 200 100
