#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sqlite3.h>

struct Student {  // 这是一个数据结构，用于存储学生信息 ，由data_source.cpp中的generateStudent函数生成
    char name[50];
    long number;
    long grade;
    char hobby[3][30];
};

std::vector<Student> students; // vector容器 ，用于存储学生信息
std::mutex students_mutex; // 互斥锁，用于保护students容器
sqlite3 *db; // SQLite数据库连接
int record_count = 0; // 记录数量
int table_count = 1; // 表数量

void createTable(const std::string& table_name) {  // 创建表
    std::string sql = "CREATE TABLE " + table_name + " ("    // 创建表的SQL语句
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, " // ID字段，自增
                      "NAME TEXT NOT NULL, "                // NAME字段，非空
                      "NUMBER INTEGER NOT NULL, "         // NUMBER字段，非空
                      "GRADE INTEGER NOT NULL, "      // GRADE字段，非空
                      "HOBBY1 TEXT, "                   // HOBBY1字段
                      "HOBBY2 TEXT, "               // HOBBY2字段
                      "HOBBY3 TEXT);";           // HOBBY3字段

    char *errMsg = nullptr; // 错误信息
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg); // 执行SQL语句
    if (rc != SQLITE_OK) { // 如果执行失败
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void insertStudent(const std::string& table_name, const Student& student) { // 插入学生信息
    std::string sql = "INSERT INTO " + table_name + " (NAME, NUMBER, GRADE, HOBBY1, HOBBY2, HOBBY3) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr); // 准备SQL语句

    sqlite3_bind_text(stmt, 1, student.name, -1, SQLITE_STATIC); // 绑定参数
    sqlite3_bind_int(stmt, 2, student.number);  // 绑定参数, 2表示第二个参数
    sqlite3_bind_int(stmt, 3, student.grade);   // 绑定参数,3表示第三个参数
    sqlite3_bind_text(stmt, 4, student.hobby[0], -1, SQLITE_STATIC);// 绑定参数
    sqlite3_bind_text(stmt, 5, student.hobby[1], -1, SQLITE_STATIC);// 绑定参数
    sqlite3_bind_text(stmt, 6, student.hobby[2], -1, SQLITE_STATIC);// 绑定参数

    int rc = sqlite3_step(stmt); // 执行SQL语句
    if (rc != SQLITE_DONE) { // 如果执行失败
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt); // 释放资源
}

void handleConnection(boost::asio::ip::tcp::socket socket) {
    try {
        while (true) { // 循环处理客户端发送的数据
            Student student; // 学生信息
            boost::system::error_code error;    // 错误码
            size_t len = boost::asio::read(socket, boost::asio::buffer(&student, sizeof(student)), error); // 读取数据

            if (error == boost::asio::error::eof) { // 如果连接被对方关闭
                break; // Connection closed cleanly by peer
            } else if (error) { // 如果发生其他错误
                throw boost::system::system_error(error); // Some other error
            }

            if (len == sizeof(student)) { // 如果读取到了完整的学生信息
                std::lock_guard<std::mutex> lock(students_mutex); // 加锁
                students.push_back(student);    // 将学生信息存入容器
                record_count++; // 记录数量加1

                if (record_count >= 1000) { // 如果记录数量超过1000 ，则将学生信息排序后存入数据库
                    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                        return a.number < b.number;
                    });

                    auto t = std::time(nullptr);// 获取当前时间
                    auto tm = *std::localtime(&t); // 转换为本地时间
                    std::ostringstream oss; // 字符串流
                    oss << std::put_time(&tm, "%Y%m%d%H%M%S"); // 格式化时间
                    std::string table_name = "Table_"+oss.str(); // 表名

                    createTable(table_name); // 创建表
                    for (const auto& s : students) { // 遍历学生信息
                        insertStudent(table_name, s);
                    }

                    students.clear(); // 清空容器
                    record_count = 0;   // 记录数量清零
                    table_count++;  // 表数量加1
                }
            }
        }
    } catch (std::exception& e) {   // 捕获异常
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

int main() {
    try {
        int rc = sqlite3_open("students.db", &db);  // 打开数据库
        if (rc) {   // 如果打开失败
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            return 1;
        }

        boost::asio::io_context io_context; // IO上下文
        // 创建一个TCP服务器，监听8080端口,接受客户端连接
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)); 

        std::cout << "Data center started, listening on port 8080..." << std::endl; // 输出提示信息

        while (true) {  // 循环处理客户端连接
            boost::asio::ip::tcp::socket socket(io_context);    // 创建一个TCP套接字
            acceptor.accept(socket);    // 接受客户端连接
            std::cout << "Accepted new connection." << std::endl;   // 输出提示信息
            std::thread(handleConnection, std::move(socket)).detach();    // 创建一个新线程处理客户端连接
        }   

        sqlite3_close(db);  // 关闭数据库
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
