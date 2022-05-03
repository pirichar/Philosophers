clear
printf "\n---------HELLO AND WELCOME TO THIS TEST------------\n\n\n\n"


printf "\033[1;35m-------This is the test for 1-short_introduction_to_threads---------\n\033[1;0m"
gcc ./1-short_intro_to_threads/short_introduction_to_threads.c -g -pthread
./a.out
rm -rf a.out.dSYM
rm -rf a.out

printf "\033[1;35m-------This is the test for 3-race_conditions---------\n\033[1;0m"
gcc ./3-race_conditions/race_conditions.c -g -pthread
./a.out
rm -rf a.out.dSYM
rm -rf a.out
