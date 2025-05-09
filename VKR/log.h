#ifndef LOG_H
#define LOG_H
#include <string>

using namespace std;

class Log
{
public:
//    static string* logfile;

    static void print(string data);
    static void print_metrix(string data);
};

#endif // LOG_H
