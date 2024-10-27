#Makefile
#SRC=main.cpp
#SRC=shell.cpp
SRC=test.cpp
TARGET=bash
LIBS=-lreadline

all: run

$(TARGET): $(SRC)
	g++ -g $(SRC) -o $(TARGET) -o $@ $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)
