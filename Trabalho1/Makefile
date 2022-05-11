SRC=./src/*.c
INCLUDE=-I./include/
BIN=./bin

all:
	gcc $(SRC) -g -lm -Wall -Werror -Wextra $(INCLUDE) -o $(BIN)

run:
	$(BIN)

clean:
	rm $(BIN)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BIN)