#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <boost/asio.hpp>
#include <ctime>
#include <iomanip>

struct Student {
    char name[50];
    long number;
    long grade;
    char hobby[3][30];
};

std::vector<Student> students;
std::mutex students_mutex;

// void handleConnection(boost::asio::ip::tcp::socket socket) {
//     try {
//         while (true) {
//             Student student;
//             boost::asio::read(socket, boost::asio::buffer(&student, sizeof(student)));
            
//             std::lock_guard<std::mutex> lock(students_mutex);
//             students.push_back(student);

//             if (students.size() >= 1000) {
//                 std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
//                     return a.number < b.number;
//                 });

//                 auto t = std::time(nullptr);
//                 auto tm = *std::localtime(&t);
//                 std::ostringstream oss;
//                 oss << std::put_time(&tm, "%Y%m%d%H%M%S") << ".txt";
//                 std::string filename = oss.str();

//                 std::ofstream file(filename);
//                 for (const auto& s : students) {
//                     file << "Number: " << s.number << ", Grade: " << s.grade << "\n";
//                 }
//                 file.close();
//                 students.clear();
//             }
//         }
//     } catch (std::exception& e) {
//         std::cerr << "Exception in thread: " << e.what() << "\n";
//     }
// }

void handleConnection(boost::asio::ip::tcp::socket socket) {
    try {
        while (true) {
            Student student;
            boost::asio::read(socket, boost::asio::buffer(&student, sizeof(student)));
            
            std::lock_guard<std::mutex> lock(students_mutex);
            students.push_back(student);

            if (students.size() >= 1000) {
                std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                    return a.number < b.number;
                });

                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::ostringstream oss;
                oss << std::put_time(&tm, "%Y%m%d%H%M%S") << ".txt";
                std::string filename = oss.str();

                std::ofstream file(filename);
                for (const auto& s : students) {
                    file << "Number: " << s.number << ", Grade: " << s.grade << "\n";
                }
                file.close();
                std::vector<Student>().swap(students);
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));

        while (true) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(handleConnection, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
