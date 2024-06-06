#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <boost/asio.hpp>
#include <cstring>

struct Student {
    char name[50];
    long number;
    long grade;
    char hobby[3][30];
};

Student generateStudent(int grade) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dist(0, 100000);

    Student student;
    student.number = dist(gen);
    student.grade = grade;
    // Populate other fields...
    std::strncpy(student.name, "John Doe", sizeof(student.name));
    std::strncpy(student.hobby[0], "Reading", sizeof(student.hobby[0]));
    std::strncpy(student.hobby[1], "Swimming", sizeof(student.hobby[1]));
    std::strncpy(student.hobby[2], "Gaming", sizeof(student.hobby[2]));
    return student;
}

void dataSource(const std::string& host, int port, int grade, int interval_ms) {
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(host, std::to_string(port)));

        while (true) {
            Student student = generateStudent(grade);
            boost::asio::write(socket, boost::asio::buffer(&student, sizeof(student)));
            std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        std::cout << "This student is dead\n";
    }
}

int main() {
    std::thread t1(dataSource, "127.0.0.1", 8080, 2, 500);
    std::thread t2(dataSource, "127.0.0.1", 8080, 3, 1000);
    t1.join();
    t2.join();
    return 0;
}
