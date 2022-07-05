all:
	g++ -std=c++17 -Wall -Wextra -Werror -pedantic main.cpp defs.cpp -o main.exe
run:
	./main
