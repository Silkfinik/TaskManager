#include "header.cpp"
#include <iostream>

void menu(Tasks &tasks);
void deadline_reminder(const Tasks &tasks);

int main() {
    Tasks tasks;
    deadline_reminder(tasks);
    menu(tasks);
    return 0;
}

void menu(Tasks &tasks) {
    std::cout << "\tMENU\n";
    std::cout << "1. Add task\n" << "2. View tasks\n" << "3. Edit task\n" << "4. Delete task\n" <<
        "5. View by status\n" << "6. Deadline checker\n" << "0. Exit\n";
    while (true) {
        switch (input_num("Enter menu num: ")) {
            case 0:
                return;
            case 1:
                tasks.add_task();
                break;
            case 2:
                tasks.view_tasks();
                break;
            case 3:
                tasks.edit_task();
                break;
            case 4:
                tasks.delete_task();
                break;
            case 5:
                tasks.view_by_status();
                break;
            case 6:
                tasks.deadline_checker();
                break;
            default:
                std::cout << "Incorrect input! Try again\n";
        }
    }
}

void deadline_reminder(const Tasks& tasks) {
    const Date time = str_to_date(Tasks::get_current_time());
    tasks.near_deadline_checker(time);
}
