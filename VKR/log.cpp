#include "log.h"
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

void Log::print(string data)
{
    time_t now_c = chrono::system_clock::to_time_t(chrono::system_clock::now());

    ofstream outFile("/Users/dmitrij/Documents/C++/Scaling_images/Log.txt", ios::app);
    if (outFile.is_open()){
        outFile << "[" << put_time(localtime(&now_c), "%F %T") << "]" << " " << data << endl;
        outFile.close();
    } else {
        cout << "Файл Log.txt не открылся" << "\n";
    }
}

void Log::print_metrix(string data)
{
    time_t now_c = chrono::system_clock::to_time_t(chrono::system_clock::now());

    ofstream outFile("/Users/dmitrij/Documents/C++/Scaling_images/metrix/Log_metrix.txt", ios::app);
    if (outFile.is_open()){
        outFile << "[" << put_time(localtime(&now_c), "%F %T") << "]" << " " << data << endl;
        outFile.close();
    } else {
        cout << "Файл Log.txt не открылся" << "\n";
    }
}
