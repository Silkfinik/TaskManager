#include "header.h"
#include <iostream>
#include <map>
#include <fstream>
#include <cctype>

void input_digit(unsigned &digit) {
    std::string str;
    std::cin >> str;
    bool flag = true;
    while (flag) {
        for (auto &i: str) {
            if (!isdigit(i)) {
                std::cout << "Incorrect input! Try again: ";
                std::cin >> str;
                break;
            }
            flag = false;
        }
    }
    digit = std::stoi(str);
}

std::string status_to_str(unsigned status){
    std::string str;
    switch (status) {
        case 0:
            str = "New";
            break;
        case 1:
            str = "In progress";
            break;
        case 2:
            str = "Done";
            break;
        default:
            str = "Unknown";
            break;
    }
    return str;
}

Date str_to_date(std::string str) {
    Date date;
    date.day = std::stoi(str.substr(0, str.find('-')));
    str.erase(0, str.find('-') + 1);
    date.month = std::stoi(str.substr(0, str.find('-')));
    str.erase(0, str.find('-') + 1);
    date.year = std::stoi(str.substr(0, str.find(' ')));
    str.erase(0, str.find(' ') + 1);
    date.hour = std::stoi(str.substr(0, str.find(':')));
    str.erase(0, str.find(':') + 1);
    date.minute = std::stoi(str);
    return date;
}

bool date_check(Date date) {
    std::map <unsigned, unsigned> days_in_month = {{1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31},
                                         {6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31},
                                         {11, 30}, {12, 31}};
    if (date.day < 1 || date.month < 1 || date.month > 12 || date.year < 1 || date.hour < 0 || date.hour > 23 || date.minute < 0
            || date.minute > 59 || date.day > days_in_month[date.month]) {
        return false;
    }
    return true;
}

void Tasks::add_task(){
    Task task;
    std::cout << "Enter task name: ";
    std::cin >> task.name;
    std::cout << "Enter task description: ";
    std::cin >> task.description;
    std::cout << "Enter task deadline (DD-MM-YYYY HH:MM):\n";
    std::cout << "Day: ";
    input_digit(task.date.day);
    std::cout << "Month: ";
    input_digit(task.date.month);
    std::cout << "Year: ";
    input_digit(task.date.year);
    std::cout << "Hour: ";
    input_digit(task.date.hour);
    std::cout << "Minute: ";
    input_digit(task.date.minute);
    while (!date_check(task.date)) {
        std::cout << "Incorrect date! Enter task date (DD-MM-YYYY HH:MM): ";
        std::cout << "Day: ";
        input_digit(task.date.day);
        std::cout << "Month: ";
        input_digit(task.date.month);
        std::cout << "Year: ";
        input_digit(task.date.year);
        std::cout << "Hour: ";
        input_digit(task.date.hour);
        std::cout << "Minute: ";
        input_digit(task.date.minute);
    }
    tasks.push_back(task);
}

void Tasks::file_to_vec() {
    std::ifstream input("Tasks.txt");
    if (!input.is_open()) {
        std::cout << "File not found!" << std::endl;
        return;
    }
    Task task;
    std::string temp;
    while (std::getline(input, temp)) {
        task.name = temp;
        std::getline(input, temp);
        task.description = temp;
        std::getline(input, temp);
        task.date = str_to_date(temp);
        std::getline(input, temp);
        task.status = std::stoi(temp);
        tasks.push_back(task);
    }
    input.close();
}

void Tasks::vec_to_file() {
    std::ofstream output("Tasks.txt", std::ios::app);
    for (auto & task : tasks) {
        output << task.name << std::endl;
        output << task.description << std::endl;
        output << task.date.day << "-" << task.date.month << "-" << task.date.year << " "
               << task.date.hour << ":" << task.date.minute << std::endl;
        output << task.status << std::endl;
    }
    output.close();
}
















void Tasks::print() {
    for (auto & task : tasks) {
        std::cout << "Task name: " << task.name << std::endl;
        std::cout << "Task description: " << task.description << std::endl;
        std::cout << "Task deadline: " << task.date.day << "-" << task.date.month << "-" << task.date.year << " "
                  << task.date.hour << ":" << task.date.minute << std::endl;
        std::cout << "Task status: " << status_to_str(task.status) << std::endl;
        std::cout << "----------------------------------------\n";
    }
}

