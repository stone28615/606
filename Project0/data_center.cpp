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

std::vector<Student> students;  // Vector容器 存储学生信息
std::mutex students_mutex;  // 互斥锁

void handleConnection(boost::asio::ip::tcp::socket socket) {
    try {
        while (true) {
            Student student;
            boost::system::error_code error; //错误码
            size_t len = boost::asio::read(socket, boost::asio::buffer(&student, sizeof(student)), error); // 阻塞

            if (error == boost::asio::error::eof) {
                break; // 连接关闭 cleanly 
            } else if (error) {
                throw boost::system::system_error(error); // Some other error
            }

            if (len == sizeof(student)) {
                std::lock_guard<std::mutex> lock(students_mutex);
                students.push_back(student);

                if (students.size() >= 1000) {
                    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) { // 按学号排序
                        return a.number < b.number;
                    });

                    auto t = std::time(nullptr); // 获取当前时间
                    auto tm = *std::localtime(&t); // 转换为本地时间
                    std::ostringstream oss; // 创建一个ostringstream对象
                    oss << std::put_time(&tm, "%Y%m%d%H%M%S") << ".txt";    // 将时间转换为字符串
                    std::string filename = "../log/" + oss.str();   // 文件名

                    std::ofstream file(filename); // 创建文件
                    for (const auto& s : students) {
                        file << "Name: " << s.name << ", Number: " << s.number << ", Grade: " << s.grade <<", hobbies: "<<s.hobby[0]<<"\t"<<s.hobby[1]<<"\t"<<s.hobby[2]<<"\n";
                    }  // 将学生信息写入文件
                    file.close();   // 关闭文件
                    students.clear();   // 清空students
                }
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

int main() {
    // 确保存在log目录
    struct stat info;
    if (stat("../log", &info) != 0 || !(info.st_mode & S_IFDIR)) {
        mkdir("../log", 0777); 
    }

    try {
        boost::asio::io_context io_context; // IO上下文
        // 创建一个TCP监听器 用于监听端口8080
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));
        // 输出提示信息
        std::cout << "Data center started, listening on port 8080..." << std::endl;

        while (true) {
            boost::asio::ip::tcp::socket socket(io_context); // 创建一个TCP套接字
            acceptor.accept(socket);    // 接受新连接
            std::cout << "Accepted new connection." << std::endl;   // 输出提示信息
            std::thread(handleConnection, std::move(socket)).detach();  // 创建一个新线程处理连接
        }
    } catch (std::exception& e) {  // 捕获异常
        std::cerr << "Exception: " << e.what() << "\n";
        std::cout << "Press Enter to exit..." << std::endl;
        return 1;
    }
    std::cout << "Data Center is ending" << std::endl;
    return 0;
}
