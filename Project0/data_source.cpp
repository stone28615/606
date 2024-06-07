#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <boost/asio.hpp>
#include <cstring>
long long student_number = 0;
struct Student {  //学生信息
    char name[50];
    long number;
    long grade;
    char hobby[3][30];
};

Student generateStudent(int grade) { //生成学生信息
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dist(0, 100000);    //生成0到100000之间的随机数

    Student student;
    student.number = dist(gen); //生成学号
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
        boost::asio::io_context io_context; //IO上下文, 用于管理IO操作
        boost::asio::ip::tcp::socket socket(io_context);    //TCP套接字
        boost::asio::ip::tcp::resolver resolver(io_context);    //解析器
        boost::asio::connect(socket, resolver.resolve(host, std::to_string(port)));   //连接到服务器

        while (true) {
            Student student = generateStudent(grade);   //生成学生信息
            boost::asio::write(socket, boost::asio::buffer(&student, sizeof(student)));   //发送学生信息
            // std::cout << "Sent student with number " << student.number << " and grade " << student.grade << "\n";   //输出学生信息
            std::cout << "Sent student with number " << student_number++ << " and grade " << student.grade << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));//线程休眠
        }
    } catch (std::exception& e) {   //异常处理
        std::cerr << "Exception: " << e.what() << "\n";
        std::cout << "This student is dead\n";
    }
}

int main() {
    std::thread t1(dataSource, "127.0.0.1", 8080, 2, 500);  //创建线程, 用于发送年级为2的学生信息
    std::thread t2(dataSource, "127.0.0.1", 8080, 3, 1000); //创建线程, 用于发送年级为3的学生信息
    t1.join();  //等待线程结束
    t2.join();  //等待线程结束
    return 0;
}
