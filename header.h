#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <utility>
#include <vector>

struct Date {
    std::string day;
    std::string month;
    std::string year;
    std::string hour;
    std::string minute;
    explicit Date (std::string d = "00", std::string m = "00", std::string y = "0000", std::string h = "00",
                  std::string min = "00") : day(std::move(d)), month(std::move(std::move(m))), year(std::move(y)), hour(std::move(h)), minute(std::move(min)) {}
};

struct Task {
    std::string name;
    std::string description;
    unsigned status;
    Date date;
    explicit Task (std::string n = "", std::string d = "", unsigned s = 0,
                  Date da = Date()) : name(std::move(n)), description(std::move(d)), status(s), date(std::move(da)) {}
};

class Tasks {
private:
    std::vector<Task> tasks;
    void file_to_vec();
    void vec_to_file() const;
public:
    Tasks() { file_to_vec(); };
    ~Tasks() { vec_to_file(); };
    void add_task();
    void view_tasks() const;
    void edit_task();
    void delete_task();
    void view_by_status() const;
    void near_deadline_checker(const Date& time) const;
    void expired_deadline_checker(const Date& time) const;
    void deadline_checker() const;
    static std::string get_current_time();
};

#endif //HEADER_H