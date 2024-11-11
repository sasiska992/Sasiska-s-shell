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

create_package: $(PATH_TO_PACKAGE)$(TARGET)
	dpkg-deb --build $(PACKAGE_NAME)
	mkdir -p packages
	mv $(PACKAGE_NAME).deb packages



# Переменные для cronfs
CRONFS_SRC = cronfs.cpp
CRONFS_TARGET = cronfs
CRONFS_PATH = $(PACKAGE_NAME)/usr/local/bin/


# Правило для сборки cronfs
$(CRONFS_PATH)$(CRONFS_TARGET): $(CRONFS_SRC)
	mkdir -p $(CRONFS_PATH)
	g++ -g $(CRONFS_SRC) -o $(CRONFS_PATH)$(CRONFS_TARGET) -lfuse


# Правило для запуска cronfs
run_cronfs: $(CRONFS_PATH)$(CRONFS_TARGET)
	./$(CRONFS_PATH)$(CRONFS_TARGET)




