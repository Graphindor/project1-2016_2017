CC=g++
FLAGS=-DEVAL -static -O2 -std=c++11 -Wall
PROJECT=pokemon

%: %.cpp
	$(CC) $(FLAGS) -o $(PROJECT) $^

test: main
	./$(PROJECT)
	@rm ./$(PROJECT) && cat output.txt && echo ""

.PHONY: clean

clean:
	@rm -f *~ $(PROJECT)
