#include <iostream>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>  // Необходим для std::istringstream
#include <readline/readline.h>
#include <readline/history.h>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <vector>
#include <array>
#include <sys/wait.h>


using namespace std;

enum Command {
    EXIT,
    ECHO,
    LS,
    CD,
    PWD,
    CLEAR,
    EXPORT,
    ENV,
    DISK,
    GET_ALL_PARTITIONS,
    UNKNOWN,
    CRON_TAB,
    UMOUNT_CRON,
};

struct Colors {
    const string RED = "\033[31m";   // Blue
    const string RESET = "\033[0m";  // Сброс цвета к стандартному
    const string YELLOW = "\033[37m";  // Сброс цвета к стандартному
} colors;
const char *history_file = ".bash_history.txt";

string exec(const string cmd) {
    array<char, 128> buffer{}; // Буфер для чтения вывода
    string result; // Строка для хранения результата

    // Открываем процесс и читаем его вывод
    unique_ptr<FILE, int (*)(FILE *)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw runtime_error("Не удалось открыть процесс!");
    }

    // Читаем вывод команды
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // Добавляем вывод в строку
    }

    return result; // Возвращаем результат
}


vector <string> split(const string &str, char delimiter) {
    vector <string> tokens;
    istringstream tokenStream(str);
    string token;

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Обработчик сигнала
void handle_signal(int signal) {
    if (signal == SIGINT) {
        cout << "\nЗавершение программы..." << endl;
        write_history(history_file); // Сохраняем историю перед выходом
        exit(0); // Завершаем программу
    }
}

bool check_echo(const string &str) {
    string is_echo;
    for (char simb: str) {
        is_echo.push_back(simb);
        if (is_echo.length() == 4 && is_echo == "echo") return true;
        if (is_echo.length() >= 4) return false;
    }
    return false;
}

string get_echo(const string &input_echo_text) {
    if (check_echo(input_echo_text)) {
        string echo_text;
        try {
            for (const char simb: input_echo_text.substr(5)) {
                echo_text.push_back(simb);
            }
            return echo_text;
        } catch (out_of_range) {
            return "";
        }
    }
    return "";
}

Command getCommand(const string &input) {
    if (input == "exit" || input == "q") return EXIT;
    if (check_echo(input)) return ECHO;
    if (input.substr(0, 2) == "ls") return LS;
    if (input.substr(0, 2) == "cd") return CD;
    if (input == "pwd") return PWD;
    if (input == "clear") return CLEAR;
    if (input.substr(0, 6) == "export") return EXPORT;
    if (input[0] == '$') return ENV;
    if (input == "disk") return DISK;
    if (input == "partitions") return GET_ALL_PARTITIONS;
    if (input == "cron_tab") return CRON_TAB;
    if (input == "umount_cron") return UMOUNT_CRON;
    return UNKNOWN;
}

string change_dir(string &path, const string &input_path) {
    string cd_dir = input_path.substr(3); // Директория для проверки
    string temp_path = path;
    temp_path.pop_back();
    string full_path = temp_path + "/" + cd_dir;
    string check_command;
    if (cd_dir.at(0) == '/' or cd_dir.at(0) == '~') {
        check_command = "test -d " + cd_dir + " && echo true || echo false";

        string check_result = exec(check_command);
        if (check_result == "true\n") {
            path = exec("cd " + cd_dir + " && pwd");
        } else {
            cout << "No such file or directory" << endl;
        }
    } else {
        check_command = "test -d " + full_path + " && echo true || echo false";

        string check_result = exec(check_command);
        if (check_result == "true\n") {
            path = exec("cd " + full_path + " && pwd");
        } else {
            cout << "No such file or directory" << endl;
        }

    }
    return path;
}

string get_disk_info() {
    string result;
    result = exec("sudo  hexdump -C /dev/nvme0n1 -n 512");
    string file_system = result.substr(result.find("000001f0"), result.find("|"));
    file_system = file_system.substr(file_system.length() - 7, 5);
    if (file_system == "55 aa") {
        return "MNT\n";
    } else {
        return "Unknown\n";
    }
}

void create_cron_vfs() {
    string crontab_info = exec("crontab -l");
    vector <string> cron_commands = split(crontab_info, '\n');
    cout << "Starting mount" << endl;
    usleep(500000);
    cout << "Mounting completed by 30%" << endl;
    usleep(500000);
    exec("mkdir -p .cronfs");
    cout << "Mounting completed by 70%" << endl;
    usleep(500000);
    exec("sudo mount -t tmpfs tmpfs .cronfs");
    cout << "Mounting completed by 90%" << endl;
    usleep(500000);
    for (string i: cron_commands) {
        if (i.length() != 0) {
            string file_name = i.substr(10, i.length() - 1);

            ofstream outfile(".cronfs/" + file_name);

            outfile << i.substr(0, 10) << std::endl;

            outfile.close();
            cout << "Create file " + file_name << endl;
            usleep(300000);
//            cout << file_name << endl;
        }
    }
    cout << "Mounting completed by 100%" << endl;
    usleep(500000);
    cout << "Mounting is done!" << endl;
}

void umount_cron_vfs() {
    cout << "Starting umount" << endl;
    usleep(500000);
    cout << "Umounting completed by 30%" << endl;
    exec("sudo umount .cronfs");
    usleep(300000);
    cout << colors.YELLOW << ".cronfs was unmouned!" << colors.RESET << endl;
    usleep(500000);
    cout << "Umounting completed by 60%" << endl;
    exec("rm -rf .cronfs");
    usleep(500000);
    cout << ".cronfs was deleted!" << endl;
    usleep(500000);
    cout << "Umounting completed by 100%" << endl;
}

int main() {
    string path = exec("pwd");
    signal(SIGINT, handle_signal);
    // Загружаем историю из файла, если он существует
    read_history(history_file);

    string input;
    while (true) {
        string folderIcon = " 📁 "; // Иконка папки
        string temp_path = path;
        path.pop_back();
        // Формируем строку для ввода
        char *line = readline(("soot@127.0.0.1" + folderIcon + path + ": ").c_str());
        path = temp_path;
        // Проверка на EOF (Ctrl+D)
        if (line == nullptr) {
            cout << colors.YELLOW << "\nSee you next time! I`m going to sleep\n";
            exit(0);
        }

        input = line; // Преобразуем char* в string
        free(line); // Освобождаем память, выделенную readline
        if (!input.empty()) {
            add_history(input.c_str()); // Добавляем ввод в историю
            switch (getCommand(input)) {
                case EXIT:
                    cout << colors.YELLOW << "\nSee you next time! I`m going to sleep\n";
                    exit(0);
                case ECHO:
                    cout << get_echo(input) << endl;
                    break;
                case CD:
                    path = change_dir(path, input);
                    break;
                case PWD:
                    __pid_t pid;
                    pid = fork();
                    if (pid == 0) {
                        char *argv[2];
                        argv[0] = line;
                        argv[1] = NULL;
                        execl("/usr/bin/pwd", line, NULL);
                        perror("execl");
                        exit(1);
                    } else {
                        if (pid < 0) {
                            perror("fork");
                        } else {
                            int status;
                            waitpid(pid, &status, 0);
                        }
                    }
                    break;
                case CLEAR:
                    cout << exec(input);
                    break;
                case EXPORT:
                    exec(input);
                    break;
                case ENV:
                    cout << exec("printenv " + input.substr(1));
                    break;
                case LS:
                    cout << exec(input + " " + path);
                    break;
                case DISK:
                    cout << get_disk_info();
                    break;
                case GET_ALL_PARTITIONS:
                    cout << exec("sudo fdisk -l");
                    break;
                case CRON_TAB:
                    create_cron_vfs();
                    break;
                case UMOUNT_CRON:
                    umount_cron_vfs();
                    break;
                case UNKNOWN:
                default:
                    string result = exec(input);
                    // 
                    if (result == "sh: 1:" + input + ": not found") {
                        cout << colors.RED << "Unknown command " + input + ". Try again" << colors.RESET << endl;
                    } else {
                        cout << result << endl;
                    }
                    break;
            }
        } else {
            cout << "Please enter some command -_-" << endl;
        }
        input.clear();// Освобождаем память
        write_history(input.c_str());
    }


    write_history(input.c_str());
    return 0;
}
