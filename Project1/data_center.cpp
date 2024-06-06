#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <ctime>
#include <iomanip>
#include <sstream>

struct Student {
    char name[50];
    long number;
    long grade;
    char hobby[3][30];
};

std::vector<Student> students;
std::mutex students_mutex;

void handleConnection(boost::asio::ip::tcp::socket socket) {
    try {
        while (true) {
            Student student;
            boost::system::error_code error; // 
            size_t len = boost::asio::read(socket, boost::asio::buffer(&student, sizeof(student)), error); // Blocking

            if (error == boost::asio::error::eof) {
                break; // Connection closed cleanly by peer
            } else if (error) {
                throw boost::system::system_error(error); // Some other error
            }

            if (len == sizeof(student)) {
                std::lock_guard<std::mutex> lock(students_mutex);
                students.push_back(student);

                if (students.size() >= 1000) {
                    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                        return a.number < b.number;
                    });

                    auto t = std::time(nullptr); // Get current time
                    auto tm = *std::localtime(&t);
                    std::ostringstream oss; // Create a string stream
                    oss << std::put_time(&tm, "%Y%m%d%H%M%S") << ".txt";
                    std::string filename = oss.str();

                    std::ofstream file(filename); // Will be closed when file goes out of scope
                    for (const auto& s : students) {
                        file << "Name: " << s.name << ", Number: " << s.number << ", Grade: " << s.grade << "\n";
                    }
                    file.close();
                    students.clear();
                }
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

        std::cout << "Data center started, listening on port 8080..." << std::endl;

        while (true) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "Accepted new connection." << std::endl;
            std::thread(handleConnection, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        std::cout << "Press Enter to exit..." << std::endl;
        return 1;
    }
    std::cout << "Data Center is ending" << std::endl;
    return 0;
}
