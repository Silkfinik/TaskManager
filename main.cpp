#include "header.cpp"
#include <iostream>
#include <ctime>

std::string get_current_time();

int main() {
    std::cout << get_current_time() << std::endl;
    Tasks tasks;
    tasks.add_task();
    tasks.print();
    return 0;
}

std::string get_current_time() {
    std::time_t currentTime = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&currentTime));
    std::string str(buffer);
    return str;
}
