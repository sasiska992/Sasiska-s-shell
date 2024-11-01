# Определите переменные
SRC = shell.cpp
TARGET = soot
LIBS = -lreadline
PACKAGE_NAME = sasiska_shell
PATH_TO_PACKAGE = $(PACKAGE_NAME)/usr/local/bin/


# Правило по умолчанию
all: run

# Правило для сборки
$(PATH_TO_PACKAGE)$(TARGET): $(SRC)
	mkdir -p $(PATH_TO_PACKAGE)
	g++ -g $(SRC) -o $(PATH_TO_PACKAGE)$(TARGET) $(LIBS)

# Правило для запуска
run: $(PATH_TO_PACKAGE)$(TARGET)
	./$(PATH_TO_PACKAGE)$(TARGET)

# Правило для очистки
clean:
	rm -rf $(PATH_TO_PACKAGE)$(TARGET)

create_package:
	dpkg-deb --build $(PACKAGE_NAME)
	mkdir -p packages
	mv $(PACKAGE_NAME).deb packages
