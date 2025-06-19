#include "log.h"
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

void Log::print(string data)
/*Функция записи строки в лог-файл Log.txt.

Параметры:
  - data(string): Строка с сообщением, которую нужно записать  в лог.*/

{
    time_t now_c = chrono::system_clock::to_time_t(chrono::system_clock::now());

    ofstream outFile("/home/sers/Desktops/Desktop1/Chubarov_astra/RGRTU/NIR_2/Log.txt", ios::app);
    if (outFile.is_open()){
        outFile << "[" << put_time(localtime(&now_c), "%F %T") << "]" << " " << data << endl;
        outFile.close();
    } else {
        cout << "Файл Log.txt не открылся" << "\n";
    }
}

//void Log::print_metrix(string data)
///*Функция записи строки в лог-файл Log_metrix.txt.

//Параметры:
//  - data(string): Строка с сообщением, которую нужно записать  в лог.*/

//{
//    time_t now_c = chrono::system_clock::to_time_t(chrono::system_clock::now());

//    ofstream outFile("/home/sers/Desktops/Desktop1/Chubarov_astra/RGRTU/NIR_2/Log_metrix.txt", ios::app);
//    if (outFile.is_open()){
//        outFile << "[" << put_time(localtime(&now_c), "%F %T") << "]" << " " << data << endl;
//        outFile.close();
//    } else {
//        cout << "Файл Log.txt не открылся" << "\n";
//    }
//}
