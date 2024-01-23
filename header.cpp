#include "header.h"
#include <iostream>
#include <map>
#include <fstream>
#include <cctype>
#include <ctime>
#include <algorithm>

void line() {
    std::cout << "----------------------------------------\n";
}

void delete_last_space(std::string &str) {
    if (str[str.size() - 1] == ' ') {
        str.erase(str.size() - 1, 1);
    }
}

bool is_str_digit(const std::string& str) {
    return std::all_of(str.begin(), str.end(), isdigit);
}

int input_num(const std::string& str){
    std::string temp;
    if (!str.empty()) {
        std::cout << str;
    }
    std::cin >> temp;
    while (!is_str_digit(temp)) {
        std::cout << "Incorrect input! Try again: ";
        std::cin >> temp;
    }
    delete_last_space(temp);
    return std::stoi(temp);
}

void input_date_memb(std::string& str) {
    std::string temp;
    std::cin >> temp;
    while (!is_str_digit(temp)) {
        std::cout << "Incorrect input! Try again: ";
        std::getline(std::cin, temp);
    }
    str = temp;
}

void date_nrm_form(Date& temp) {
    if (temp.day.size() < 2) {
        temp.day = "0" + temp.day;
    }
    if (temp.month.size() < 2) {
        temp.month = "0" + temp.month;
    }
    if (temp.hour.size() < 2) {
        temp.hour = "0" + temp.hour;
    }
    if (temp.minute.size() < 2) {
        temp.minute = "0" + temp.minute;
    }
}

void input_date(Date& date) {
    std::cout << "Enter day: ";
    input_date_memb(date.day);
    std::cout << "Enter month: ";
    input_date_memb(date.month);
    std::cout << "Enter year: ";
    input_date_memb(date.year);
    std::cout << "Enter hour: ";
    input_date_memb(date.hour);
    std::cout << "Enter minute: ";
    input_date_memb(date.minute);
    date_nrm_form(date);
}

bool date_checker(const Date& date) {
    std::map <std::string, std::string> months = {{"01", "31"}, {"02", "28"}, {"03", "31"}, {"04", "30"}, {"05", "31"},
                                                  {"06", "30"}, {"07", "31"}, {"08", "31"}, {"09", "30"}, {"10", "31"},
                                                  {"11", "30"}, {"12", "31"}};
    if (date.month > "12" || date.month.size() > 2) {
        std::cout << "Invalid month! Try again\n";
        return false;
    }
    if (months[date.month] < date.day || date.day.size() > 2) {
        std::cout << "Invalid day! Try again\n";
        return false;
    }
    if (date.hour > "24" || date.hour.size() > 2) {
        std::cout << "Invalid hour! Try again\n";
        return false;
    }
    if (date.minute > "60" || date.minute.size() > 2) {
        std::cout << "Invalid minute! Try again\n";
        return false;
    }
    return true;
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
    date.day = str.substr(0, str.find('-'));
    str.erase(0, str.find('-') + 1);
    date.month = str.substr(0, str.find('-'));
    str.erase(0, str.find('-') + 1);
    date.year = str.substr(0, str.find(' '));
    str.erase(0, str.find(' ') + 1);
    date.hour = str.substr(0, str.find(':'));
    str.erase(0, str.find(':') + 1);
    date.minute = str;
    return date;
}

void print_task(const Task& task) {
    std::cout << "\nTask name: " << task.name << std::endl;
    std::cout << "Task description: " << task.description << std::endl;
    std::cout << "Task deadline: " << task.date.day << "-" << task.date.month << "-" << task.date.year << " "
              << task.date.hour << ":" << task.date.minute << std::endl;
    std::cout << "Task status: " << status_to_str(task.status) << std::endl;
    line();
}

void Tasks::add_task(){
    Task task;
    std::cout << "Enter task name: ";
    while (task.name.empty()) {
        std::getline(std::cin, task.name);
        delete_last_space(task.name);
    }
    std::cout << "Enter task description: ";
    while (task.description.empty()) {
        std::getline(std::cin, task.description);
        delete_last_space(task.description);
    }
    std::cout << "Enter task deadline (dd-mm-yyyy hh:mm):\n";
    input_date(task.date);
    while (!date_checker(task.date)) {
        input_date(task.date);
    }
    task.status = 0;
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

void Tasks::vec_to_file() const {
    std::ofstream output("Tasks.txt");
    for (auto & task : tasks) {
        output << task.name << std::endl;
        output << task.description << std::endl;
        output << task.date.day << "-" << task.date.month << "-" << task.date.year << " "
               << task.date.hour << ":" << task.date.minute << std::endl;
        output << task.status << std::endl;
    }
    output.close();
}

void Tasks::view_tasks() const {
    int counter = 1;
    line();
    for (auto & task : tasks) {
        std::cout << "Task number: " << counter++ << std::endl;
        std::cout << "Task name: " << task.name << std::endl;
        std::cout << "Task status: " << status_to_str(task.status) << std::endl;
        line();
    }
    std::cout << "1. View task\n" << "0. Back\n";
    int choice = input_num("Enter your choice: ");
    while (choice < 0 || choice > 1) {
        std::cout << "Incorrect input! Try again: ";
        choice = input_num("Enter your choice: ");
    }
    if (choice == 0) {
        return;
    }
    int task_num = input_num("Enter task number: ");
    while (task_num < 1 || task_num > tasks.size()) {
        std::cout << "Incorrect input! Try again: ";
        task_num = input_num("Enter task number: ");
    }
    std::cout << "----------------------------------------";
    print_task(tasks[task_num - 1]);
}

void Tasks::edit_task() {
    int task_num = input_num("Enter task number: ");
    while (task_num < 1 || task_num > tasks.size()) {
        std::cout << "Incorrect input! Try again: ";
        task_num = input_num("Enter task number: ");
    }
    std::cout << "What do you want to edit?\n" << "1. Name\n" << "2. Description\n"
    << "3. Deadline\n" << "4. Status\n" << "0. Exit\n" << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    while (choice < 0 || choice > 4) {
        std::cout << "Incorrect input! Try again: ";
        std::cin >> choice;
    }
    std::string temp;
    switch (choice) {
        case 0:
            return;
        case 1:
            std::cout << "Enter new name: ";
            std::getline(std::cin, temp);
            while (temp.empty()) {
                std::getline(std::cin, temp);
                delete_last_space(temp);
            }
            tasks[task_num - 1].name = temp;
            break;
        case 2:
            std::cout << "Enter new description: ";
            std::getline(std::cin, temp);
            while (temp.empty()) {
                std::getline(std::cin, temp);
                delete_last_space(temp);
            }
            tasks[task_num - 1].description = temp;
            break;
        case 3:
            std::cout << "Enter new deadline (dd-mm-yyyy hh:mm):\n";
            input_date(tasks[task_num - 1].date);
            while (!date_checker(tasks[task_num - 1].date)) {
                input_date(tasks[task_num - 1].date);
            }
            break;
        case 4:
            std::cout << "Enter new status:\n" << "1. In progress\n" << "2. Done\n" << "Enter your choice: ";
            std::cin >> tasks[task_num - 1].status;
            while (tasks[task_num - 1].status < 1 || tasks[task_num - 1].status > 2) {
                std::cout << "Incorrect input! Try again: ";
                std::cin >> tasks[task_num - 1].status;
            }
            break;
        default:
            std::cout << "Something went wrong. Try again\n";
            break;
    }
}

void Tasks::delete_task() {
    int task_num = input_num("Enter task number: ");
    while (task_num < 1 || task_num > tasks.size()) {
        std::cout << "Incorrect input! Try again: ";
        task_num = input_num("Enter task number: ");
    }
    task_num--;
    tasks.erase(tasks.begin() + task_num);
}

void Tasks::view_by_status() const{
    std::cout << "Enter status:\n" << "0. New\n" << "1. In progress\n" << "2. Done\n" << "Enter your choice: ";
    int choice = input_num("");
    while (choice < 0 || choice > 2) {
        std::cout << "Incorrect input! Try again: ";
        choice = input_num("");
    }
    int counter = 1;
    bool flag = false;
    for (auto &i : tasks) {
        if (i.status == choice) {
            if (!flag) {
                line();
            }
            std::cout << "Task number: " << counter++;
            print_task(i);
            flag = true;
        }
    }
    if (!flag) {
        std::cout << "None\n";
    }
}

std::string Tasks::get_current_time() {
    const std::time_t currentTime = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", std::localtime(&currentTime));
    std::string str(buffer);
    return str;
}

void Tasks::near_deadline_checker(const Date& time) const{
    std::cout << "Tasks with deadline in 24 hours:\n";
    bool flag = false;
    int counter = 1;

    for (auto & i : tasks) {
        if (i.date.year == time.year && i.date.month == time.month && i.date.day == time.day) {
            if (std::stoi(i.date.hour) - std::stoi(time.hour) <= 24) {
                if (!flag) {
                    line();
                }
                std::cout << "Task number: " << counter;
                print_task(i);
                flag = true;
            }
        } else if (i.date.year == time.year && i.date.month == time.month &&
            std::stoi(i.date.day) == std::stoi(time.day) + 1 && std::stoi(i.date.hour) - std::stoi(time.hour) <= 24) {
            if (!flag) {
                line();
            }
            std::cout << "Task number: " << counter;
            print_task(i);
            flag = true;
        }
        counter++;
    }
    if (!flag) {
        std::cout << "None\n";
    }
}

void Tasks::expired_deadline_checker(const Date& time) const{
    std::cout << "Expired tasks:\n";
    bool flag = false;
    int counter = 1;
    for (auto &i : tasks) {
        if (i.date.year < time.year) {
            if (!flag) {
                line();
            }
            std::cout << "Task number: " << counter;
            print_task(i);
            flag = true;
        } else if (i.date.year == time.year && i.date.month < time.month) {
            if (!flag) {
                line();
            }
            std::cout << "Task number: " << counter;
            print_task(i);
            flag = true;
        } else if (i.date.year == time.year && i.date.month == time.month && i.date.day < time.day) {
            if (!flag) {
                line();
            }
            std::cout << "Task number: " << counter;
            print_task(i);
            flag = true;
        } else if (i.date.year == time.year && i.date.month == time.month && i.date.day == time.day) {
            if (i.date.hour < time.hour) {
                if (!flag) {
                    line();
                }
                std::cout << "Task number: " << counter;
                print_task(i);
                flag = true;
            } else if (i.date.hour == time.hour && i.date.minute < time.minute) {
                if (!flag) {
                    line();
                }
                std::cout << "Task number: " << counter;
                print_task(i);
                flag = true;
            }
        }
        counter++;
    }
    if (!flag) {
        std::cout << "None\n";
    }
}

void Tasks::deadline_checker() const{
    const Date time = str_to_date(get_current_time());
    near_deadline_checker(time);
    expired_deadline_checker(time);
}