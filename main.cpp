#include "header.cpp"
#include <iostream>

std::string get_current_time();

int main() {
    std::cout << get_current_time() << std::endl;
    Tasks tasks;
    tasks.view_tasks();
    tasks.view_by_status();
    return 0;
}