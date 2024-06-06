#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <boost/asio.hpp>

struct Student {
    std::string name;
    long number;
    long grade;
    std::string hobby[3];
};

Student generateStudent(int grade) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dist(0, 100000);

    Student student;
    student.number = dist(gen);
    student.grade = grade;
    // Populate other fields...
    return student;
}

void dataSource(const std::string& host, int port, int grade, int interval_ms) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);
    socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port));

    while (true) {
        Student student = generateStudent(grade);
        boost::asio::write(socket, boost::asio::buffer(&student, sizeof(student)));
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

int main() {
    std::thread t1(dataSource, "127.0.0.1", 9999, 2, 500);
    std::thread t2(dataSource, "127.0.0.1", 9999, 3, 1000);
    t1.join();
    t2.join();
    return 0;
}
