#Makefile
#SRC=main.cpp
#SRC=shell.cpp
SRC=test.cpp
TARGET=soot
LIBS=-lreadline
PATH_TO_PACKAGE=package/usr/bin/
all: run

$(TARGET): $(SRC)
	g++ -g $(SRC) -o $(PATH_TO_PACKAGE)$(TARGET) -o $@ $(LIBS)

run: $(TARGET)
	./$(TARGET)


clean:
	rm -rf $(TARGET)
