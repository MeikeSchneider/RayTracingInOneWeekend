compile:
	g++ main.cpp -o main.exe

TEST_FILES := $(wildcard tests/*.cpp)
test:
	g++ $(TEST_FILES) -o test.exe
	./test.exe

clean:
	rm *.exe