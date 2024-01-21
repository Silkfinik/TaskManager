#include <string>
#include <utility>
#include <vector>

struct Date {
    unsigned day;
    unsigned month;
    unsigned year;
    unsigned hour;
    unsigned minute;
    explicit Date (unsigned d = 0, unsigned m = 0, unsigned y = 0, unsigned h = 0, unsigned min = 0) : day(d),
                                                                             month(m), year(y), hour(h), minute(min) {}
};

struct Task {
    std::string name;
    std::string description;
    unsigned status;
    Date date;
    explicit Task (std::string n = "", std::string d = "", unsigned s = 0,
                  Date da = Date()) : name(std::move(n)), description(std::move(d)), status(s), date(da) {}
};

class Tasks {
private:
    std::vector<Task> tasks;
    void file_to_vec();
    void vec_to_file();
public:
    Tasks() { file_to_vec(); };
    ~Tasks() { vec_to_file(); };
    void add_task();
    void print();
};