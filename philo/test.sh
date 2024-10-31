# const color
GREEN_BG="\033[42;1m"
RED_BG="\033[41;1m"
YEL_BG="\033[43;1m"
BLU_BG="\033[44m"
END="\033[m"

# check for good init
echo "${RED_BG}<------------------- Issue in args -------------------->${END}"
echo "\n"
echo "${YEL_BG}./philo 1 800 200 -200${END}"
./philo 1 800 200 -200
echo "${BLU_BG}valgrind --leak-check=full ./philo 1 800 200 -200${END}"
valgrind --leak-check=full ./philo 1 800 200 -200
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 -200${END}"
valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 -200
echo "\n"
echo "${YEL_BG}./philo 1 800 200 a${END}"
./philo 1 800 200 a
echo "${BLU_BG}valgrind --leak-check=full ./philo 1 800 200 a${END}"
valgrind --leak-check=full ./philo 1 800 200 a
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 a${END}"
valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 a
echo "\n"
echo "${YEL_BG}./philo 1 800 200 12345678912${END}"
./philo 1 800 200 12345678912
echo "${BLU_BG}valgrind --leak-check=full ./philo 1 800 200 12345678912${END}"
valgrind --leak-check=full ./philo 1 800 200 12345678912
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 12345678912${END}"
valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 12345678912
echo "\n"
echo "${YEL_BG}./philo 1 800 200 2147483648${END}"
./philo 1 800 200 2147483648
echo "${BLU_BG}valgrind --leak-check=full ./philo 1 800 200 2147483648${END}"
valgrind --leak-check=full ./philo 1 800 200 2147483648
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 2147483648${END}"
valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 2147483648
echo "\n"
echo "${YEL_BG}./philo 1 800 200 0${END}"
./philo 1 800 200 0
echo "${BLU_BG}valgrind --leak-check=full ./philo 1 800 200 0${END}"
valgrind --leak-check=full ./philo 1 800 200 0
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 0${END}"
valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 0
echo "\n"
echo "${YEL_BG}./philo 201 800 200 200${END}"
./philo 201 800 200 200
echo "${BLU_BG}valgrind --leak-check=full ./philo 201 800 200 200${END}"
valgrind --leak-check=full ./philo 201 800 200 200
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 201 800 200 200${END}"
valgrind --tool=helgrind --history-level=approx ./philo 201 800 200 200
echo "\n"
echo "${YEL_BG}./philo 200 800 59 200${END}"
./philo 200 800 59 200
echo "${BLU_BG}valgrind --leak-check=full ./philo 200 800 59 200${END}"
valgrind --leak-check=full ./philo 200 800 59 200
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 200 800 59 200${END}"
valgrind --tool=helgrind --history-level=approx ./philo 200 800 59 200
echo "\n"

# Routine terminate with one death
echo "${RED_BG}<------------------- One philo should die -------------------->${END}"
echo "${YEL_BG}./philo 1 800 200 200${END}"
./philo 1 800 200 200
echo "${BLU_BG}valgrind --leak-check=full ./philo 1 800 200 20${END}"
valgrind --leak-check=full ./philo 1 800 200 200
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 200${END}"
valgrind --tool=helgrind --history-level=approx ./philo 1 800 200 200
echo "\n"
echo "${YEL_BG}./philo 4 310 200 100${END}"
./philo 4 310 200 100
echo "${BLU_BG}valgrind --leak-check=full ./philo 4 310 200 100${END}"
valgrind --leak-check=full ./philo 4 310 200 100
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 4 310 200 100${END}"
valgrind --tool=helgrind --history-level=approx ./philo 4 310 200 100
echo "\n"

# Routine terminate with no death and 7 meals
echo "${GREEN_BG}<------------------- No philo should die for 7 meals-------------------->${END}"
echo "${YEL_BG}./philo 5 800 200 200 7${END}"
./philo 5 800 200 200 7
echo "${BLU_BG}valgrind --leak-check=full ./philo 5 800 200 200 7${END}"
valgrind --leak-check=full ./philo 5 800 200 200 7
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 5 800 200 200 7${END}"
valgrind --tool=helgrind --history-level=approx ./philo 5 800 200 200 7
echo "\n"
echo "${YEL_BG}./philo 4 410 200 200 7${END}"
./philo 4 410 200 200 7
echo "${BLU_BG}valgrind --leak-check=full ./philo 4 410 200 200 7${END}"
valgrind --leak-check=full ./philo 4 410 200 200 7
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 4 410 200 200 7${END}"
valgrind --tool=helgrind --history-level=approx ./philo 4 410 200 200 7
echo "\n"

# Routine must be infini
echo "${GREEN_BG}<------------------- No philo should die with infini loop -------------------->${END}"
echo "${YEL_BG}./philo 4 410 200 200${END}"
./philo 4 410 200 200
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 4 410 200 200${END}"
valgrind --tool=helgrind --history-level=approx ./philo 4 410 200 200
echo "\n"
echo "${YEL_BG}./philo 5 800 200 200${END}"
./philo 5 800 200 200
echo "${BLU_BG}valgrind --tool=helgrind --history-level=approx ./philo 5 800 200 200${END}"
valgrind --tool=helgrind --history-level=approx ./philo 5 800 200 200
echo "\n"