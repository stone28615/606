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

int main(){
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d%H%M%S") << ".txt";
        std::string filename = "log/" + oss.str();

        std::ofstream file(filename);
        file<<"this is a test\n";
        file.close();
}