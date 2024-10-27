//#include <iostream>
//#include <fstream>
//#include <ncurses.h>
//#include <vector>
//#include <ncurses.h>
//
//using namespace std;
//const string RED = "\033[31m";   // Blue
//const string RESET = "\033[0m";  // Сброс цвета к стандартному
//
//vector<string> loadHistory(const string &filename) {
//    vector<string> history;
//    ifstream file(filename);
//    string line;
//
//    while (getline(file, line)) {
//        history.push_back(line);
//    }
//
//    return history;
//}
//
//bool check_echo(const string &str) {
//    string is_echo;
//    for (char simb: str) {
//        is_echo.push_back(simb);
//        if (is_echo.length() == 4 && is_echo == "echo") return true;
//    }
//    return false;
//}
//
//string get_echo(const string &input_echo_text) {
//    if (check_echo(input_echo_text)) {
//        string echo_text;
//        for (const char simb: input_echo_text.substr(5)) {
//            echo_text.push_back(simb);
//        }
//        return echo_text;
//    } else return "Input some text, please =(";
//}
//
//int main() {
//    initscr();                   // Переход в curses-режим
//    printw("Hello world!\n");  // Отображение приветствия в буфер
//    refresh();                   // Вывод приветствия на настоящий экран
////    getch();                     // Ожидание нажатия какой-либо клавиши пользователем
//    keypad(stdscr, TRUE); // Включаем поддержку специальных клавиш (например, стрелок)
//
//    ofstream out;
//    out.open(".bash_history.txt", std::ios::app);
//    string input;
//    while (true) {
//        printw("soot@127.0.0.1: ");
//        char str[100], input_char; // Массив для хранения введенной строки
//        int str_index = 0;
////        while (true) {
//////            printw("hi");
////            input_char = getch();
////            str[str_index] = input_char;
////            str_index++;
//////            getch();                     // Ожидание нажатия какой-либо клавиши пользователем
//////            clear();
////            addch(str[input_char]);
////            if (input_char == '\n') {
////                break;
////            }
////        }
//        while (true) {
//            input_char = getch();
//            str[str_index] = input_char;
//            str_index++;
//
//            if (input_char == '\n') { // Проверяем, нажата ли клавиша Enter
//                break; // Выходим из цикла
//            } else {
//
//                clear();
//                addch(input_char);
//            }
//        }
////        addstr("123");
//        // Создаем std::string из массива символов
//        string inputString(str);
//        printw(inputString.c_str());
//        refresh();
//        if (input == "exit") exit(1);
//        if (check_echo(input)) cout << get_echo(input) << endl;
//        else {
//            cout << RED << "Unknown command. Try again" << RESET << endl;
//        }
//
//        if (input.empty()) {
//            exit(1);
//        }
//
//        if (out.is_open()) {
//            out << input << endl;
//        }
//
//        out.close();
//    }
//    endwin();                    // Выход из curses-режима. Обязательная команда.
//}
//
